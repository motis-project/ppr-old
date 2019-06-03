#pragma once

#include "footrouting/preprocessing/statistics.h"

namespace footrouting {

struct routing_graph;

namespace preprocessing {

struct int_graph;

void add_linked_crossings(int_graph&, routing_graph&,
                          routing_graph_statistics&);

}  // namespace preprocessing
}  // namespace footrouting
