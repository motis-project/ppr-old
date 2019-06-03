#pragma once

#include "footrouting/preprocessing/osm_graph/osm_graph.h"
#include "footrouting/preprocessing/statistics.h"

namespace footrouting {
namespace preprocessing {

void move_crossings(osm_graph& og, osm_graph_statistics& stats);

}  // namespace preprocessing
}  // namespace footrouting
