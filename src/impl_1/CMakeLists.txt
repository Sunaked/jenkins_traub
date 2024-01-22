cmake_minimum_required(VERSION 3.10)

project(jenkins_traub_impl_1)

set(CMAKE_CXX_STANDARD 20)

#find_package(Boost 1.82 REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Add your source files here
set(SOURCES 
  main.cpp
  fin_polynomial_roots_jenkins_traub.cpp
  fin_polynomial_roots_jenkins_traub.hpp
  polynomial.cpp
  polynomial.hpp
  )

# Specify the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Boost::boost
  Eigen3::Eigen
  )

