#pragma once

#include <unordered_map>

#include "footrouting/common/geometry/merc.h"
#include "footrouting/preprocessing/names.h"
#include "footrouting/preprocessing/osm_graph/osm_area.h"
#include "footrouting/preprocessing/osm_graph/osm_edge.h"
#include "footrouting/preprocessing/osm_graph/osm_node.h"

namespace footrouting {
namespace preprocessing {

struct osm_graph {
  void create_in_edges() {
    for (auto const& node : nodes_) {
      for (auto& edge : node->out_edges_) {
        edge.to_->in_edges_.emplace_back(&edge);
      }
    }
  }

  void count_edges() {
    for (auto& node : nodes_) {
      for (auto& edge : node->out_edges_) {
        if (edge.info_->type_ == edge_type::STREET) {
          node->street_edges_++;
        } else if (edge.info_->type_ == edge_type::FOOTWAY) {
          node->footway_edges_++;
        }
      }
      for (auto edge : node->in_edges_) {
        if (edge->info_->type_ == edge_type::STREET) {
          node->street_edges_++;
        } else if (edge->info_->type_ == edge_type::FOOTWAY) {
          node->footway_edges_++;
        }
      }
    }
  }

  std::vector<std::unique_ptr<osm_node>> nodes_;
  data::vector<data::unique_ptr<edge_info>> edge_infos_;
  std::vector<std::unique_ptr<osm_area>> areas_;
  names_vector_t names_;
  names_map_t names_map_;
};

}  // namespace preprocessing
}  // namespace footrouting
