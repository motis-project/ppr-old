#pragma once

#include "footrouting/preprocessing/options.h"

namespace footrouting {

struct routing_graph;

namespace preprocessing {

void calc_crossing_detours(routing_graph&, options const&);

}  // namespace preprocessing
}  // namespace footrouting
