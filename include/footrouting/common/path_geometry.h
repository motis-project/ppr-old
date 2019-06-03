#pragma once

#include <vector>

#include "boost/geometry/geometries/register/linestring.hpp"

#include "footrouting/common/data.h"

BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED(std::vector)
BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED(footrouting::data::vector)
