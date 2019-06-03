#pragma once

#include "footrouting/common/routing_graph.h"

namespace footrouting {
namespace serialization {

void read_routing_graph(routing_graph& rg, std::string const& filename);

}  // namespace serialization
}  // namespace footrouting
