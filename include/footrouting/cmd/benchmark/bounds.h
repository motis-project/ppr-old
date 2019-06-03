#pragma once

#include "footrouting/common/location.h"
#include "footrouting/common/location_geometry.h"

namespace footrouting {
namespace benchmark {

class bounds {
public:
  virtual ~bounds() = default;
  bounds() = default;
  bounds(bounds const&) = delete;
  bounds& operator=(bounds const&) = delete;
  bounds(bounds&&) = delete;
  bounds& operator=(bounds&&) = delete;

  virtual bool contains(location const& loc) const = 0;
  virtual location random_pt() = 0;
};

}  // namespace benchmark
}  // namespace footrouting
