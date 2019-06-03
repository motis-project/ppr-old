#include <cstdio>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include "boost/filesystem.hpp"

#include "conf/options_parser.h"

#include "footrouting/backend/server.h"
#include "footrouting/cmd/backend/prog_options.h"
#include "footrouting/cmd/preprocess/prog_options.h"
#include "footrouting/common/timing.h"
#include "footrouting/preprocessing/preprocessing.h"

using namespace footrouting;
using namespace footrouting::backend;
using namespace footrouting::preprocessing;

namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {
  preprocessing::prog_options pp_opt;
  backend::prog_options be_opt;
  conf::options_parser parser({&pp_opt, &be_opt});
  parser.read_command_line_args(argc, argv);

  if (parser.help()) {
    parser.print_help(std::cout);
    return 0;
  } else if (parser.version()) {
    return 0;
  }

  parser.read_configuration_file();

  parser.print_unrecognized(std::cout);
  parser.print_used(std::cout);

  if (!boost::filesystem::exists(pp_opt.osm_file_)) {
    std::cerr << "File not found: " << pp_opt.osm_file_ << std::endl;
    return 1;
  }

  statistics stats;

  auto const t_start = timing_now();
  routing_graph rg = build_routing_graph(pp_opt.get_options(), stats);
  auto const t_after_build = timing_now();
  stats.d_total_pp_ = ms_between(t_start, t_after_build);

  std::cout << "Routing graph: " << rg.data_->nodes_.size() << " nodes, "
            << rg.data_->areas_.size() << " areas" << std::endl;

  std::cout << "Creating r-trees..." << std::endl;
  fs::remove(fs::path("routing-graph.ppr.ert"));
  fs::remove(fs::path("routing-graph.ppr.art"));
  rg.prepare_for_routing();
  auto const t_after_rtree = timing_now();
  auto const d_rtree = ms_between(t_after_build, t_after_rtree);

  print_timing("Preprocessing", stats.d_total_pp_);
  print_timing("R-Tree Generation", d_rtree);

  // HTTP SERVER

  ppr_server(rg, be_opt.http_host_, be_opt.http_port_, be_opt.threads_);

  return 0;
}
