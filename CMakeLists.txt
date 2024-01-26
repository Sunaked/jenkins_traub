cmake_minimum_required(VERSION 3.10)

project(jenkins_traub)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.82 REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Add your source files here
set(SOURCES 
  src/main.cpp
  src/newton.h
  src/newton.cpp
  src/next_step.h
  src/next_step.cpp
  src/synthetic_division.cpp
  src/synthetic_division.h
)

# For google tests

# Specify the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Boost::boost
  Eigen3::Eigen
  GTest::gtest_main)

