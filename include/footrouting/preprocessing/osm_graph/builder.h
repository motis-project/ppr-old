#pragma once

#include <string>
#include <vector>

#include "footrouting/preprocessing/options.h"
#include "footrouting/preprocessing/osm_graph/osm_graph.h"
#include "footrouting/preprocessing/statistics.h"

namespace footrouting {
namespace preprocessing {

osm_graph build_osm_graph(options const& opt, statistics& stats);

}  // namespace preprocessing
}  // namespace footrouting
