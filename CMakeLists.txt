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
  newton.cc
  src/next_step.h
  src/next_step.cpp
  src/synthetic_division.cpp
  src/synthetic_division.h
)

# For google tests
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Specify the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Boost::boost
  Eigen3::Eigen
  GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
