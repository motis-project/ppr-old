#pragma once

#include <string>
#include <vector>

#include "footrouting/common/routing_graph.h"

namespace footrouting {
namespace backend {
namespace output {

std::string to_graph_response(
    std::vector<routing_graph::edge_rtree_value_type> const&,
    std::vector<routing_graph::area_rtree_value_type> const&,
    routing_graph const&, bool include_visibility_graphs);

}  // namespace output
}  // namespace backend
}  // namespace footrouting
