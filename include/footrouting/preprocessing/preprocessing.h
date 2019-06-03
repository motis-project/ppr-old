#pragma once

#include <string>

#include "footrouting/preprocessing/int_graph/int_graph.h"
#include "footrouting/preprocessing/options.h"
#include "footrouting/preprocessing/statistics.h"

namespace footrouting {
namespace preprocessing {

routing_graph build_routing_graph(options const& opt, statistics& stats);

}  // namespace preprocessing
}  // namespace footrouting
