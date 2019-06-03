#pragma once

#include <cstring>

#include "footrouting/common/enums.h"

namespace footrouting {
namespace preprocessing {
namespace osm {

inline wheelchair_type::wheelchair_type get_wheelchair_type(
    char const* wheelchair_tag) {
  if (strcmp(wheelchair_tag, "yes") == 0 ||
      strcmp(wheelchair_tag, "designated") == 0) {
    return wheelchair_type::YES;
  } else if (strcmp(wheelchair_tag, "no") == 0) {
    return wheelchair_type::NO;
  } else if (strcmp(wheelchair_tag, "limited") == 0) {
    return wheelchair_type::LIMITED;
  } else {
    return wheelchair_type::UNKNOWN;
  }
}

}  // namespace osm
}  // namespace preprocessing
}  // namespace footrouting
