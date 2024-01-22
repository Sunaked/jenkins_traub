cmake_minimum_required(VERSION 3.10...3.22)
project(benchmark)


set(CMAKE_CXX_STANDARD 20)


find_package(benchmark REQUIRED)

set(SOURCES
  hello_bench.cc)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)

