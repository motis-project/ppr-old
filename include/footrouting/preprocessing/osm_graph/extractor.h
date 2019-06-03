#pragma once

#include <string>

#include "footrouting/preprocessing/options.h"
#include "footrouting/preprocessing/osm_graph/osm_graph.h"
#include "footrouting/preprocessing/statistics.h"

namespace footrouting {
namespace preprocessing {

osm_graph extract(std::string const& osm_file, options const& opt,
                  statistics& stats);

}  // namespace preprocessing
}  // namespace footrouting
