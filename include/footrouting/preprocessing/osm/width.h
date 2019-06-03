#pragma once

#include "osmium/osm/tag.hpp"

#include "footrouting/common/routing_graph.h"

namespace footrouting {
namespace preprocessing {
namespace osm {

double get_actual_width(osmium::TagList const& tags, double def);

double get_render_width(footrouting::edge_type edge,
                        footrouting::street_type street);

}  // namespace osm
}  // namespace preprocessing
}  // namespace footrouting
