#pragma once

#include <string>

#include "ppr/common/routing_graph.h"

namespace ppr::backend {

void ppr_server(routing_graph const& rg, std::string const& http_host,
                std::string const& http_port, int num_threads);

}  // namespace ppr::backend
