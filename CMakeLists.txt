cmake_minimum_required(VERSION 3.10.2)
project(container-copy-benchmark LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

add_subdirectory(benchmark)

add_executable(benchmarks benchmarks.cpp)
target_link_libraries(benchmarks benchmark::benchmark benchmark::benchmark_main)
