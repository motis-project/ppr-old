#include "footrouting/serialization/reader.h"

#include "boost/filesystem.hpp"

#include "footrouting/preprocessing/names.h"
#include "footrouting/serialization/mode.h"

namespace fs = boost::filesystem;

namespace footrouting::serialization {

void read_routing_graph(routing_graph& rg, std::string const& filename) {
  if (!fs::exists(filename)) {
    throw std::runtime_error{"ppr routing graph file not found"};
  }
  rg.data_buffer_ = cista::file(filename.c_str(), "r").content();
  rg.data_ = data::deserialize<routing_graph_data, SERIALIZATION_MODE>(
      rg.data_buffer_);
  rg.filename_ = filename;
}

}  // namespace footrouting::serialization
