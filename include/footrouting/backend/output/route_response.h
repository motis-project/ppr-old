#pragma once

#include <string>
#include <vector>

#include "footrouting/common/routing_graph.h"
#include "footrouting/routing/search.h"

namespace footrouting {
namespace backend {
namespace output {

std::string routes_to_route_response(footrouting::routing::search_result const&,
                                     bool full);

}  // namespace output
}  // namespace backend
}  // namespace footrouting
