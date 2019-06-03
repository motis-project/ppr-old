#pragma once

#include "footrouting/common/geometry/merc.h"

namespace footrouting {

using area_polygon_t = boost::geometry::model::polygon<merc, false>;
using inner_area_polygon_t = boost::geometry::model::polygon<merc, true>;

}  // namespace footrouting
