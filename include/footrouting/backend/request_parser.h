#include "rapidjson/document.h"

#include "footrouting/common/location.h"

#include "footrouting/profiles/parse_search_profile.h"

namespace footrouting {
namespace backend {

inline void get_waypoints(std::vector<location>& waypoints,
                          rapidjson::Value const& doc, char const* key) {
  if (doc.HasMember(key)) {
    auto const& val = doc[key];
    if (val.IsArray()) {
      for (auto i = 0U; i < val.Size() - 1; i += 2) {
        waypoints.emplace_back(
            make_location(val[i].GetDouble(), val[i + 1].GetDouble()));
      }
    }
  }
}

inline void get_profile(footrouting::routing::search_profile& profile,
                        rapidjson::Value const& doc, char const* key) {
  if (doc.HasMember(key)) {
    profiles::parse_search_profile(profile, doc[key]);
  }
}

}  // namespace backend
}  // namespace footrouting
