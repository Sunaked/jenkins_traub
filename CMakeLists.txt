cmake_minimum_required(VERSION 3.10)

project(jenkins_traub)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.82 REQUIRED)

# Add your source files here
set(SOURCES 
  src/main.cpp
)


# Specify the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Boost::boost)
