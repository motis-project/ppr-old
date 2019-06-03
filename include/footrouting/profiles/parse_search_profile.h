#pragma once

#include <string>

#include "rapidjson/document.h"

#include "footrouting/routing/search_profile.h"

namespace footrouting {
namespace profiles {

footrouting::routing::search_profile parse_search_profile(std::string const& s);

void parse_search_profile(footrouting::routing::search_profile& profile,
                          rapidjson::Value const& root);

}  // namespace profiles
}  // namespace footrouting
