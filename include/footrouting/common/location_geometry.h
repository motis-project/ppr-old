#pragma once

#include <vector>

#include "boost/geometry.hpp"
#include "boost/geometry/algorithms/length.hpp"
#include "boost/geometry/geometries/register/point.hpp"

#include "footrouting/common/data.h"
#include "footrouting/common/location.h"
#include "footrouting/common/math.h"

BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(
    footrouting::location, double,
    boost::geometry::cs::spherical_equatorial<boost::geometry::degree>,
    footrouting::location::lon, footrouting::location::lat,
    footrouting::location::set_lon, footrouting::location::set_lat);

namespace footrouting {

template <typename Location>
double distance(Location const& a, Location const& b) {
  return boost::geometry::distance(a, b) * AVG_EARTH_RADIUS;
}

template <typename Location>
double distance(Location const& a, std::vector<Location> const& b) {
  return boost::geometry::distance(a, b) * AVG_EARTH_RADIUS;
}

template <typename Location>
double distance(Location const& a, data::vector<Location> const& b) {
  return boost::geometry::distance(a, b) * AVG_EARTH_RADIUS;
}

template <typename Location>
double length(std::vector<Location> const& path) {
  return boost::geometry::length(path) * AVG_EARTH_RADIUS;
}

template <typename Location>
double length(data::vector<Location> const& path) {
  return static_cast<double>(boost::geometry::length(path)) * AVG_EARTH_RADIUS;
}

}  // namespace footrouting
