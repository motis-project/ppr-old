#pragma once

#include "osmium/osm/tag.hpp"

namespace footrouting {
namespace preprocessing {
namespace osm {

int8_t get_layer(osmium::TagList const& tags);

}  // namespace osm
}  // namespace preprocessing
}  // namespace footrouting
