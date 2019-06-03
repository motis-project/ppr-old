#pragma once

#include <string>

#include "footrouting/preprocessing/statistics.h"

namespace footrouting {
namespace preprocessing {

void write_stats(statistics const& s, std::string const& filename);

}  // namespace preprocessing
}  // namespace footrouting
