#pragma once

#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>

#include "footrouting/common/routing_graph.h"
#include "footrouting/routing/route.h"
#include "footrouting/routing/search_profile.h"
#include "footrouting/routing/statistics.h"

namespace footrouting {
namespace routing {

struct search_result {
  std::vector<std::vector<route>> routes_;
  routing_statistics stats_;

  int total_route_count() const {
    return std::accumulate(begin(routes_), end(routes_), 0,
                           [](auto const& sum, auto const& routes) {
                             return sum + static_cast<int>(routes.size());
                           });
  }

  int destinations_reached() const {
    return static_cast<int>(
        std::count_if(begin(routes_), end(routes_),
                      [](auto const& routes) { return !routes.empty(); }));
  }
};

enum class search_direction { FWD, BWD };

search_result find_routes(routing_graph const& g, location const& start,
                          std::vector<location> const& destinations,
                          search_profile const& profile,
                          search_direction dir = search_direction::FWD,
                          bool allow_expansion = true);

}  // namespace routing
}  // namespace footrouting
