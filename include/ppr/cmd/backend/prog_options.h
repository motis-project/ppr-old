#pragma once

#include <string>
#include <thread>

#include "boost/program_options.hpp"

#include "conf/simple_config.h"

namespace ppr::backend {

class prog_options : public conf::simple_config {
public:
  explicit prog_options(
      std::string const& graph_file = "routing-graph.ppr",
      std::string const& http_host = "0.0.0.0",
      std::string const& http_port = "9042",
      int threads = static_cast<int>(std::thread::hardware_concurrency()),
      std::size_t edge_rtree_max_size = 1024UL * 1024 * 1024 * 3,
      std::size_t area_rtree_max_size = 1024UL * 1024 * 1024,
      bool lock_rtrees = false, bool prefetch_rtrees = false,
      bool verify_graph = true)
      : simple_config("Options") {
    string_param(graph_file_, graph_file, "graph,g", "Routing graph file");
    string_param(http_host_, http_host, "host", "HTTP host");
    string_param(http_port_, http_port, "port", "HTTP port");
    int_param(threads_, threads, "routing-threads",
              "Number of routing threads");
    size_t_param(edge_rtree_max_size_, edge_rtree_max_size,
                 "edge-rtree-max-size", "Maximum size for edge r-tree file");
    size_t_param(area_rtree_max_size_, area_rtree_max_size,
                 "area-rtree-max-size", "Maximum size for area r-tree file");
    bool_param(lock_rtrees_, lock_rtrees, "lock-rtrees",
               "Prefetch and lock r-trees in memory");
    bool_param(prefetch_rtrees_, prefetch_rtrees, "prefetch-rtrees",
               "Prefetch r-trees");
    bool_param(verify_graph_, verify_graph, "verify-graph",
               "Verify routing graph file");
  }

  std::string graph_file_;
  std::string http_host_;
  std::string http_port_;
  int threads_{static_cast<int>(std::thread::hardware_concurrency())};
  std::size_t edge_rtree_max_size_{};
  std::size_t area_rtree_max_size_{};
  bool lock_rtrees_{};
  bool prefetch_rtrees_{};
  bool verify_graph_{};
};

}  // namespace ppr::backend
