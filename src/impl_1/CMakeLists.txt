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
  find_polynomial_roots_jenkins_traub.hpp
  polynomial.cpp
  polynomial.hpp
  )

# Specify the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Boost::boost
  Eigen3::Eigen
  )

