#pragma once

#include "cista/serialization.h"

namespace footrouting {

constexpr auto const SERIALIZATION_MODE =
    cista::mode::WITH_INTEGRITY | cista::mode::WITH_VERSION;

}  // namespace footrouting
