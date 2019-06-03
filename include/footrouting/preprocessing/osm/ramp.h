#pragma once

#include "osmium/osm/tag.hpp"

#include "footrouting/common/tri_state.h"

namespace footrouting {
namespace preprocessing {
namespace osm {

inline tri_state::tri_state get_ramp(char const* str) {
  if (str != nullptr) {
    if (strcmp(str, "yes") == 0) {
      return tri_state::YES;
    } else if (strcmp(str, "no") == 0) {
      return tri_state::NO;
    } else if (strcmp(str, "automatic") == 0 || strcmp(str, "manual") == 0) {
      // luggage ramps
      return tri_state::YES;
    }
  }
  return tri_state::UNKNOWN;
}

// enum class ramp_type { ANY, STROLLER, BICYCLE, WHEELCHAIR, LUGGAGE };

inline tri_state::tri_state get_wheelchair_ramp(osmium::TagList const& tags) {
  auto result = get_ramp(tags["ramp:wheelchair"]);
  if (result == tri_state::UNKNOWN) {
    result = get_ramp(tags["ramp"]);
  }
  return result;
}

}  // namespace osm
}  // namespace preprocessing
}  // namespace footrouting
