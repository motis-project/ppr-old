#pragma once

#include "footrouting/common/routing_graph.h"
#include "footrouting/routing/additional_edges.h"
#include "footrouting/routing/input_pt.h"

namespace footrouting {
namespace routing {

node* create_area_node(node* input_node, input_pt const& pt,
                       additional_edges& additional);
void create_area_edges(additional_edges& additional);

}  // namespace routing
}  // namespace footrouting
