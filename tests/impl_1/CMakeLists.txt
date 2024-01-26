cmake_minimum_required(VERSION 3.14...3.22)
project(tests_impl1 LANGUAGES CXX)

# GoogleTest requires at least C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(Boost 1.81.0 REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


set(PROJECT_DIR ${PROJECT_SOURCE_DIR}/../..)

add_executable(
	${PROJECT_NAME}
	find_polynomial_roots_jenkins_traub_test.cc
  ${PROJECT_DIR}/src/impl_1/polynomial.cpp
  ${PROJECT_DIR}/src/impl_1/find_polynomial_roots_jenkins_traub.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_DIR}/")  
target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
  Boost::boost
)

message(STATUS "PROJECT_SOURCE_DIR" ${PROJECT_SOURCE_DIR})
message(STATUS "CMAKE_SOURCE_DIR" ${CMAKE_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
