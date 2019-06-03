#pragma once

#include <algorithm>
#include <string>
#include <thread>
#include <vector>

#include "boost/program_options.hpp"

#include "conf/simple_config.h"

#include "ppr/preprocessing/options.h"

namespace ppr::preprocessing {

class prog_options : public conf::simple_config {
public:
  explicit prog_options(
      std::string const& osm_file = "germany-latest.osm.pbf",
      std::string const& graph_file = "routing-graph.ppr",
      int elevation_sampling_interval = 30, int crossing_detours_limit = 600,
      bool print_warnings = false, bool move_crossings = false,
      bool create_rtrees = true,
      int threads = static_cast<int>(std::thread::hardware_concurrency()),
      std::size_t edge_rtree_max_size = 1024UL * 1024 * 1024 * 3,
      std::size_t area_rtree_max_size = 1024UL * 1024 * 1024,
      bool verify_graph = true)
      : simple_config("Preprocessing Options") {
    string_param(osm_file_, osm_file, "osm,o", "OSM dataset");
    string_param(graph_file_, graph_file, "graph,g", "output file");
    multitoken_param(dem_files_, "dem", "DEM (elevation) files");
    int_param(elevation_sampling_interval_, elevation_sampling_interval,
              "dem-interval",
              "Elevation sampling interval (meters, 0 to disable)");
    int_param(crossing_detours_limit_, crossing_detours_limit, "detours-limit",
              "Limit for unmarked crossing detours (meters)");
    bool_param(print_warnings_, print_warnings, "warnings", "Print warnings");
    bool_param(move_crossings_, move_crossings, "move-crossings",
               "Move nodes away from junctions");
    bool_param(create_rtrees_, create_rtrees, "create-rtrees",
               "Create r-tree files");
    int_param(threads_, threads, "threads", "Number of threads");
    size_t_param(edge_rtree_max_size_, edge_rtree_max_size,
                 "edge-rtree-max-size", "Maximum size for edge r-tree file");
    size_t_param(area_rtree_max_size_, area_rtree_max_size,
                 "area-rtree-max-size", "Maximum size for area r-tree file");
    bool_param(verify_graph_, verify_graph, "verify-graph",
               "Verify generated graph file");
  }

  options get_options() const {
    options opt;
    opt.osm_file_ = osm_file_;
    opt.dem_files_ = dem_files_;
    opt.elevation_sampling_interval_ =
        static_cast<double>(elevation_sampling_interval_);
    opt.crossing_detours_limit_ = static_cast<double>(crossing_detours_limit_);
    opt.print_warnings_ = print_warnings_;
    opt.move_crossings_ = move_crossings_;
    opt.threads_ = static_cast<unsigned>(std::max(1, threads_));
    return opt;
  }

  std::string osm_file_;
  std::string graph_file_;
  std::vector<std::string> dem_files_;
  int elevation_sampling_interval_{30};
  int crossing_detours_limit_{600};
  bool print_warnings_{false};
  bool move_crossings_{false};
  bool create_rtrees_{true};
  bool verify_graph_{true};
  int threads_{static_cast<int>(std::thread::hardware_concurrency())};
  std::size_t edge_rtree_max_size_{};
  std::size_t area_rtree_max_size_{};
};

}  // namespace ppr::preprocessing
