#pragma once

#include "footrouting/cmd/benchmark/csv_writer.h"
#include "footrouting/cmd/benchmark/query.h"
#include "footrouting/routing/statistics.h"

namespace footrouting {
namespace benchmark {

struct stats_writer {
  explicit stats_writer(std::string const& filename);
  void write(routing_query const& query,
             footrouting::routing::search_result const& result);

private:
  csv_writer csv_;
  std::size_t lines_;
};

}  // namespace benchmark
}  // namespace footrouting
