cmake_minimum_required(VERSION 3.10)

project(jenkins_traub_impl_1)

set(CMAKE_CXX_STANDARD 20)

#find_package(Boost 1.82 REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Boost 1.8.0 COMPONENTS boost)


# Add your source files here
set(SOURCES 
  main.cpp
  find_polynomial_roots_jenkins_traub.cpp
  polynomial.cpp
  ../framework.h
  )

# Specify the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/../../")
target_link_libraries(${PROJECT_NAME} PRIVATE
  Boost::boost
  Eigen3::Eigen
  )

