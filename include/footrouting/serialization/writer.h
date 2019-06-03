#pragma once

#include "footrouting/common/routing_graph.h"
#include "footrouting/preprocessing/statistics.h"

namespace footrouting {
namespace serialization {

void write_routing_graph(routing_graph const& rg, std::string const& filename,
                         footrouting::preprocessing::statistics& stats);

}  // namespace serialization
}  // namespace footrouting
