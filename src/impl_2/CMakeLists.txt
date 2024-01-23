cmake_minimum_required(VERSION 3.10)

project(jenkins_traub_impl_2)

set(CMAKE_CXX_STANDARD 20)

# Add your source files here
set(SOURCES 
  main.cpp
  JenkinsTraub.cpp
  )

# Specify the executable
add_executable(${PROJECT_NAME} ${SOURCES})


