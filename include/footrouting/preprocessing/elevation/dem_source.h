#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "footrouting/common/elevation.h"
#include "footrouting/common/location.h"

namespace footrouting {
namespace preprocessing {
namespace elevation {

struct dem_source {
  dem_source();
  ~dem_source();
  dem_source(dem_source const&) = delete;
  dem_source& operator=(dem_source const&) = delete;
  dem_source(dem_source&&) = delete;
  dem_source& operator=(dem_source&&) = delete;

  void add_file(std::string const& filename);

  elevation_t get(location const& loc) const;

private:
  struct impl;
  std::unique_ptr<impl> impl_;
};

}  // namespace elevation
}  // namespace preprocessing
}  // namespace footrouting
