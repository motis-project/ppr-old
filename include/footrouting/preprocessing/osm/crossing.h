#pragma once

#include "osmium/osm.hpp"

#include "footrouting/common/enums.h"

namespace footrouting {
namespace preprocessing {
namespace osm {

crossing_type::crossing_type get_crossing_type(osmium::TagList const& tags);

}  // namespace osm
}  // namespace preprocessing
}  // namespace footrouting
