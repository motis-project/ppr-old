#pragma once

#include <string>
#include <thread>

#include "boost/program_options.hpp"

#include "conf/simple_config.h"

namespace footrouting {
namespace benchmark {

class prog_options : public conf::simple_config {
public:
  explicit prog_options(
      std::string const& graph_file = "routing-graph.bin",
      std::string const& station_file = "", std::string const& bbox = "",
      std::string const& poly_file = "",
      std::string const& spec_file = "benchmark.toml",
      int threads = static_cast<int>(std::thread::hardware_concurrency()),
      int warmup = 10, int queries = 1000, bool verbose = false,
      bool override = false)
      : simple_config("Options") {
    string_param(graph_file_, graph_file, "graph,g", "Routing graph");
    string_param(station_file_, station_file, "stations,s",
                 "Public transport station file (dbkoord_geo.101)");
    string_param(spec_file_, spec_file, "spec", "Spec file");
    string_param(bbox_, bbox, "bbox,b",
                 "Bounding box for points/stations "
                 "(bot_left_lon,bot_left_lat,top_right_lon,top_right_lat)");
    string_param(poly_file_, poly_file, "poly",
                 "Poly file for points/stations");
    int_param(threads_, threads, "threads,t", "Number of threads");
    int_param(warmup_, warmup, "warmup",
              "Number of warmup queries (per thread)");
    int_param(queries_, queries, "queries,n", "Number of queries (total)");
    bool_param(verbose_, verbose, "verbose,v", "Verbose output");
    bool_param(override_, override, "override",
               "Override existing output files");
  }

  std::string graph_file_;
  std::string station_file_;
  std::string spec_file_;
  std::string bbox_;
  std::string poly_file_;
  int warmup_{10};
  int queries_{1000};
  int threads_{static_cast<int>(std::thread::hardware_concurrency())};
  bool verbose_{false};
  bool override_{false};
};

}  // namespace benchmark
}  // namespace footrouting
