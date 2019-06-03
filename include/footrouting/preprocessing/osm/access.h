#pragma once

#include "osmium/osm.hpp"

namespace footrouting {
namespace preprocessing {
namespace osm {

bool access_allowed(char const* access, bool def);

bool access_allowed(osmium::TagList const& tags, bool def);

}  // namespace osm
}  // namespace preprocessing
}  // namespace footrouting
