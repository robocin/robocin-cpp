########################################################################################################################

if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif ()

if (NOT CMAKE_CXX_STANDARD_REQUIRED)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()

message("-- Using C++: ${CMAKE_CXX_STANDARD}")

########################################################################################################################

# set CMAKE_EXPORT_COMPILE_COMMANDS to ON to generate a compile_commands.json file in the build directory by default
# this file is used by clang tools such as clangd, clang-tidy and clang-format

if (NOT CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif ()

########################################################################################################################

# find Threads package
find_package(Threads REQUIRED)

########################################################################################################################

# find Google Test package
# it enable the following variables:
#   GTest::gtest                          the gtest library
#   GTest::gtest_main                     the gtest_main library, which is used to link against the main function
#   GTest::gmock                          the gmock library
#   GTest::gmock_main                     the gmock_main library, which is used to link against the main function

# find GTest installation
# looks for GTest cmake config files installed by GTest's cmake installation.
find_package(GTest CONFIG REQUIRED HINTS "/opt/googletest")
message(STATUS "Using GTest: ${GTest_VERSION}")

include(GoogleTest) # provided by CMake

enable_testing() # enable testing for the entire project

########################################################################################################################

# find Google Benchmark package
# it enable the following variables:
#   benchmark::benchmark                  the benchmark library
#   benchmark::benchmark_main             the benchmark_main library, which is used to link against the main function

# find Google Benchmark installation
# looks for Google Benchmark cmake config files installed by Google Benchmark's cmake installation.
find_package(benchmark CONFIG REQUIRED HINTS "/opt/benchmark")
message(STATUS "Using Google Benchmark: ${benchmark_VERSION}")

########################################################################################################################
