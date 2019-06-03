#pragma once

#include <memory>
#include <string>

#include "net/http/server/route_request_handler.hpp"

#include "ppr/common/routing_graph.h"

namespace ppr::backend {

struct http_server {
  http_server(boost::asio::io_service& ios,
              boost::asio::io_service& thread_pool, routing_graph const&);
  ~http_server();
  http_server(http_server const&) = delete;
  http_server& operator=(http_server const&) = delete;
  http_server(http_server&&) = delete;
  http_server& operator=(http_server&&) = delete;

  void listen(std::string const& host, std::string const& port);
  void stop();

private:
  struct impl;
  std::unique_ptr<impl> impl_;
};

}  // namespace ppr::backend
