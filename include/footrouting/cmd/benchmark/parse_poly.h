#pragma once

#include <memory>
#include <string>

#include "footrouting/cmd/benchmark/poly.h"

namespace footrouting {
namespace benchmark {

std::unique_ptr<poly> parse_poly(std::string const& filename);

}  // namespace benchmark
}  // namespace footrouting
