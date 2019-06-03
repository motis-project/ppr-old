#pragma once

#include "osmium/osm/tag.hpp"

#include "footrouting/common/enums.h"

namespace footrouting {
namespace preprocessing {
namespace osm {

surface_type get_surface_type(char const* tag);

smoothness_type get_smoothness_type(char const* tag);

}  // namespace osm
}  // namespace preprocessing
}  // namespace footrouting
