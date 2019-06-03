#include "net/http/server/query_router.hpp"
#include "net/http/server/server.hpp"

#include "ppr/backend/http_server.h"
#include "ppr/backend/output/graph_response.h"
#include "ppr/backend/output/route_response.h"
#include "ppr/backend/params.h"
#include "ppr/backend/request_parser.h"
#include "ppr/profiles/json.h"
#include "ppr/profiles/parse_search_profile.h"
#include "ppr/routing/search.h"

using namespace net::http::server;
namespace srv = net::http::server;

namespace bgi = boost::geometry::index;

using namespace ppr::backend::output;
using namespace ppr::routing;
using namespace ppr::profiles;

namespace ppr::backend {

void add_cors_cache(reply& rep) {
  rep.headers.emplace_back("Access-Control-Max-Age", "3600");
}

struct route_request {
  std::vector<location> waypoints_;
  search_profile profile_;
  bool preview_{};
};

struct graph_request {
  std::vector<location> waypoints_;
  bool include_areas_{};
  bool include_visibility_graphs_{};
};

rapidjson::Document parse_json(std::string const& s) {
  rapidjson::Document doc;
  doc.Parse<rapidjson::kParseDefaultFlags>(s.c_str());
  if (doc.HasParseError()) {
    std::cerr << "json parse error" << std::endl;
  }
  return doc;
}

route_request parse_route_request(srv::route_request const& req) {
  route_request r{};
  auto doc = parse_json(req.content);
  get_waypoints(r.waypoints_, doc, "waypoints");
  get_profile(r.profile_, doc, "profile");
  get_bool(r.preview_, doc, "preview");
  return r;
}

graph_request parse_graph_request(srv::route_request const& req) {
  graph_request r{};
  auto doc = parse_json(req.content);
  get_waypoints(r.waypoints_, doc, "waypoints");
  get_bool(r.include_areas_, doc, "include_areas");
  get_bool(r.include_visibility_graphs_, doc, "include_visibility_graphs");
  return r;
}

struct http_server::impl {
  impl(boost::asio::io_service& ios, boost::asio::io_service& thread_pool,
       routing_graph const& g)
      : ios_(ios), thread_pool_(thread_pool), graph_(g), server_(ios) {
    server_.set_cors_enabled(true);
  }

  void handle_route(srv::route_request const& req, srv::callback const& cb) {
    auto rep = reply::stock_reply(reply::ok);
    rep.headers.emplace_back(header("Content-Type", "application/json"));
    add_cors_cache(rep);

    auto const r = parse_route_request(req);
    if (r.waypoints_.size() < 2) {
      rep.status = reply::bad_request;
      rep.content = R"({"error": "Missing request waypoints"})";
      return cb(rep);
    }

    auto const& start = r.waypoints_.front();
    auto const& destination = r.waypoints_.back();
    auto const result = find_routes(graph_, start, {destination}, r.profile_);
    rep.content = routes_to_route_response(result, !r.preview_);

    cb(rep);
  }

  void handle_graph(srv::route_request const& req, srv::callback const& cb) {
    auto rep = reply::stock_reply(reply::ok);
    rep.headers.emplace_back(header("Content-Type", "application/json"));
    add_cors_cache(rep);

    auto const r = parse_graph_request(req);
    if (r.waypoints_.size() < 2) {
      rep.status = reply::bad_request;
      rep.content = R"({"error": "Missing request points"})";
      return cb(rep);
    }

    auto query_box =
        boost::geometry::return_envelope<routing_graph::rtree_box_type>(
            r.waypoints_);

    std::vector<routing_graph::edge_rtree_value_type> edge_results;
    graph_.edge_rtree_->query(bgi::intersects(query_box),
                              std::back_inserter(edge_results));

    std::vector<routing_graph::area_rtree_value_type> area_results;
    if (r.include_areas_) {
      graph_.area_rtree_->query(bgi::intersects(query_box),
                                std::back_inserter(area_results));
    }

    rep.content = to_graph_response(edge_results, area_results, graph_,
                                    r.include_visibility_graphs_);
    cb(rep);
  }

  template <typename Fn>
  void run_parallel(Fn handler, srv::route_request const& req,
                    srv::callback const& cb) {
    thread_pool_.post([req, cb, handler, this]() {
      handler(req, [req, cb, this](srv::reply const& res) {
        ios_.post([cb, res]() { cb(res); });
      });
    });
  }

  void listen(std::string const& host, std::string const& port) {
    router_.route(
        "POST", "/route(/.*)?",
        [this](srv::route_request const& req, srv::callback const& cb) {
          run_parallel(
              [this](srv::route_request const& req1, srv::callback const& cb1) {
                handle_route(req1, cb1);
              },
              req, cb);
        });
    router_.route(
        "POST", "/graph(/.*)?",
        [this](srv::route_request const& req, srv::callback const& cb) {
          run_parallel(
              [this](srv::route_request const& req1, srv::callback const& cb1) {
                handle_graph(req1, cb1);
              },
              req, cb);
        });
    router_.route("OPTIONS", ".*",
                  [](srv::request const&, srv::callback const& cb) {
                    reply rep;
                    rep.status = reply::ok;
                    add_cors_cache(rep);
                    return cb(rep);
                  });
    server_.listen(host, port, router_);
  }

  void stop() { server_.stop(); }

private:
  boost::asio::io_service& ios_;
  boost::asio::io_service& thread_pool_;
  routing_graph const& graph_;
  query_router router_;
  server server_;
};

http_server::http_server(boost::asio::io_service& ios,
                         boost::asio::io_service& thread_pool,
                         routing_graph const& g)
    : impl_(new impl(ios, thread_pool, g)) {}

http_server::~http_server() = default;

void http_server::listen(std::string const& host, std::string const& port) {
  impl_->listen(host, port);
}

void http_server::stop() { impl_->stop(); }

}  // namespace ppr::backend
