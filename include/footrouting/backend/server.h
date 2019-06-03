#pragma once

#include <string>

#include "footrouting/common/routing_graph.h"

namespace footrouting {
namespace backend {

void ppr_server(routing_graph const& rg, std::string const& http_host,
                std::string const& http_port, int num_threads);

}  // namespace backend
}  // namespace footrouting
