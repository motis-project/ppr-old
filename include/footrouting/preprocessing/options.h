#pragma once

#include <string>
#include <thread>
#include <vector>

namespace footrouting {
namespace preprocessing {

struct options {
  std::string osm_file_;
  std::vector<std::string> dem_files_;

  double elevation_sampling_interval_ = 30;  // meters
  double crossing_detours_limit_ = 600;  // meters

  bool print_warnings_ = true;
  bool move_crossings_ = false;
  unsigned threads_ = std::thread::hardware_concurrency();
};

}  // namespace preprocessing
}  // namespace footrouting
