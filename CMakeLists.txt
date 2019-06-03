set(CMAKE_USER_MAKE_RULES_OVERRIDE
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cxx_flag_overrides.cmake)

cmake_minimum_required(VERSION 3.0)
project(footrouting)

# Quickfix for GCC 7
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-Wno-implicit-fallthrough)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

# Quickfix for MSVC
if (MSVC)
  add_definitions(/D_HAS_AUTO_PTR_ETC)
  add_definitions(/D_USE_MATH_DEFINES)
  add_definitions(/DNOMINMAX)
  add_definitions(/D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
  add_definitions(-D_WIN32_WINNT=0x0501)
endif()

################################
# Basic Compiler Flags
################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(ppr-compile-flags
    -fno-strict-aliasing
    -Weverything
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-missing-prototypes
    -Wno-padded
    -Wno-newline-eof
    -Wno-switch-enum
    -Wno-weak-vtables
    -Wno-gnu-zero-variadic-macro-arguments
    -Wno-unknown-pragmas
  )
elseif(NOT MSVC)
  set(ppr-compile-flags
    -Wall
    -Wextra
    -Wno-unknown-pragmas
  )
else()
  set(ppr-compile-flags
    /W3
  )
endif()

if(MINGW)
  add_definitions(-DWINVER=0x0501)
  add_definitions(-D_WIN32_WINNT=0x0501)
  add_definitions(-D_WIN32_IE=0x0501)
  add_definitions(-DBOOST_THREAD_USE_LIB)
  set(NETWORKING ws2_32 mswsock)
endif()

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


################################
# Dependencies
################################
if (MSVC)
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_MULTITHREADED ON)
  set(Boost_USE_STATIC_RUNTIME ON)
endif()
find_package(Boost REQUIRED system filesystem thread program_options iostreams)
find_package(Threads)

include(cmake/pkg.cmake)


################################
# Linter
################################
option(PPR_LINT "Run clang-tidy with the compiler." OFF)
if(PPR_LINT)
  # clang-tidy will be run on all targets defined hereafter
  include(cmake/clang-tidy.cmake)
endif()


################################
# ppr-routing library
################################
file(GLOB_RECURSE ppr-routing-files
  src/routing/*.cc
  src/serialization/reader.cc
)
add_library(ppr-routing ${ppr-routing-files})
target_include_directories(ppr-routing PUBLIC include)
target_include_directories(ppr-routing PUBLIC ${CMAKE_BINARY_DIR}/generated)
target_include_directories(ppr-routing SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(ppr-routing
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  utl
  cista
)
target_compile_features(ppr-routing PUBLIC cxx_std_17)
target_compile_options(ppr-routing PRIVATE ${ppr-compile-flags})


################################
# ppr-profiles library
################################
file(GLOB_RECURSE ppr-profiles-files
  src/profiles/*.cc
)
add_library(ppr-profiles ${ppr-profiles-files})
target_include_directories(ppr-profiles PUBLIC include)
target_include_directories(ppr-profiles SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(ppr-profiles
  rapidjson
)
target_compile_features(ppr-profiles PUBLIC cxx_std_17)
target_compile_options(ppr-profiles PRIVATE ${ppr-compile-flags})


################################
# ppr-preprocess executable
################################
file(GLOB_RECURSE ppr-preprocess-files
  src/cmd/preprocess/*.cc
  src/preprocessing/*.cc
  src/serialization/writer.cc
  src/serialization/reader.cc
)
add_executable(ppr-preprocess ${ppr-preprocess-files})
target_include_directories(ppr-preprocess PUBLIC include)
target_include_directories(ppr-preprocess PUBLIC ${CMAKE_BINARY_DIR}/generated)
target_include_directories(ppr-preprocess SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(ppr-preprocess
  zlibstatic
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  conf
  utl
  osmium
  protozero
  cista
)
target_compile_features(ppr-preprocess PUBLIC cxx_std_17)
target_compile_options(ppr-preprocess PRIVATE ${ppr-compile-flags})


################################
# ppr-backend executable
################################
file(GLOB_RECURSE ppr-backend-files
  src/cmd/backend/*.cc
  src/backend/*.cc
)
add_executable(ppr-backend ${ppr-backend-files})
target_include_directories(ppr-backend SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(ppr-backend
  zlibstatic
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  net-http_server
  conf
  ppr-routing
  ppr-profiles
  rapidjson
)
target_compile_features(ppr-backend PUBLIC cxx_std_17)
target_compile_options(ppr-backend PRIVATE ${ppr-compile-flags})


################################
# footrouting executable
################################
file(GLOB_RECURSE footrouting-files
  src/cmd/footrouting/*.cc
  src/backend/*.cc
  src/preprocessing/*.cc
)
add_executable(footrouting ${footrouting-files})
target_include_directories(footrouting SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(footrouting
  zlibstatic
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  net-http_server
  conf
  ppr-routing
  ppr-profiles
  osmium
  protozero
  rapidjson
)
target_compile_features(footrouting PUBLIC cxx_std_17)
target_compile_options(footrouting PRIVATE ${ppr-compile-flags})


################################
# ppr-benchmark executable
################################
file(GLOB_RECURSE ppr-benchmark-files
  src/cmd/benchmark/*.cc
  src/profiles/parse_search_profile.cc
)
add_executable(ppr-benchmark ${ppr-benchmark-files})
target_include_directories(ppr-benchmark SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(ppr-benchmark
  zlibstatic
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  conf
  ppr-routing
  cpptoml
  osmium
  protozero
  rapidjson
)
target_compile_features(ppr-benchmark PUBLIC cxx_std_17)
target_compile_options(ppr-benchmark PRIVATE ${ppr-compile-flags})


################################
# clang-format check
################################
add_custom_target(ppr-format-check
  find
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  -type f
  (
  -name "*.cc"
  -o
  -name "*.h"
  )
  -print0
  | xargs -0 clang-format-8 -i
  COMMAND
  git status --porcelain | xargs -I {} -0 test -z \"{}\"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Checking source code formatting"
  VERBATIM
)
