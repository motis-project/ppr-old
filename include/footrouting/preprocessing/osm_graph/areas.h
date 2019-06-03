#pragma once

#include "footrouting/preprocessing/options.h"
#include "footrouting/preprocessing/osm_graph/osm_graph.h"
#include "footrouting/preprocessing/statistics.h"

namespace footrouting {
namespace preprocessing {

void process_areas(osm_graph& graph, options const& opt,
                   osm_graph_statistics& stats);

}  // namespace preprocessing
}  // namespace footrouting
