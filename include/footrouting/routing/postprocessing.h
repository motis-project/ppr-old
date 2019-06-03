#pragma once

#include "footrouting/routing/search.h"

namespace footrouting {
namespace routing {

void postprocess_result(search_result& result, search_profile const& profile);

}  // namespace routing
}  // namespace footrouting
