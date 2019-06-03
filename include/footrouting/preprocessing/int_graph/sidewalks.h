#pragma once

#include "footrouting/common/geometry/merc.h"

namespace footrouting {
namespace preprocessing {

std::pair<std::vector<merc>, std::vector<merc>> generate_sidewalk_paths(
    std::vector<merc> const& way_path, double width);

}  // namespace preprocessing
}  // namespace footrouting
