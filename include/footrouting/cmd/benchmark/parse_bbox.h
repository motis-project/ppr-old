#pragma once

#include <memory>
#include <string>

#include "footrouting/cmd/benchmark/bbox.h"

namespace footrouting {
namespace benchmark {

std::unique_ptr<bbox> parse_bbox(std::string const& input);

}  // namespace benchmark
}  // namespace footrouting
