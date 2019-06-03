#pragma once

#include "footrouting/cmd/benchmark/bench_spec.h"
#include "footrouting/cmd/benchmark/bounds.h"
#include "footrouting/cmd/benchmark/prog_options.h"
#include "footrouting/cmd/benchmark/stations.h"
#include "footrouting/common/routing_graph.h"
#include "footrouting/routing/search_profile.h"

namespace footrouting {
namespace benchmark {

void run_benchmark(routing_graph const& rg, prog_options const& opt,
                   stations& st, bounds& a, bench_spec const& spec);

}  // namespace benchmark
}  // namespace footrouting
