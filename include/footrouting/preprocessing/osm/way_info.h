#pragma once

#include "osmium/osm.hpp"

#include "footrouting/common/routing_graph.h"
#include "footrouting/preprocessing/osm_graph/osm_graph.h"

namespace footrouting {
namespace preprocessing {
namespace osm {

struct way_info {
  way_info() = default;
  way_info(edge_info* info, bool sidewalk_left, bool sidewalk_right,
           double width, int8_t layer)
      : include_(true),
        edge_info_(info),
        sidewalk_left_(sidewalk_left),
        sidewalk_right_(sidewalk_right),
        width_(width),
        layer_(layer) {}

  bool include_{false};
  edge_info* edge_info_{nullptr};
  bool sidewalk_left_{false};
  bool sidewalk_right_{false};
  double width_{0.0};
  int8_t layer_{0};
};

way_info get_way_info(const osmium::Way& way, osm_graph& graph);

}  // namespace osm
}  // namespace preprocessing
}  // namespace footrouting
