#pragma once

#include "footrouting/preprocessing/elevation/dem_source.h"
#include "footrouting/preprocessing/osm_graph/osm_graph.h"
#include "footrouting/preprocessing/statistics.h"

namespace footrouting {
namespace preprocessing {

void add_elevation_data(osm_graph& og, elevation::dem_source& dem,
                        double sampling_interval, elevation_statistics& stats);

}  // namespace preprocessing
}  // namespace footrouting
