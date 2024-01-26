cmake_minimum_required(VERSION 3.10)

project(jenkins_traub_impl_2)

set(CMAKE_CXX_STANDARD 20)


# Add your source files here
set(SOURCES 
  main.cpp
  JenkinsTraub.cpp
  utils.hpp
  ${PROJECT_SOURCE_DIR}/../../include/framework.h
  )

# Specify the executable
add_executable(${PROJECT_NAME} ${SOURCES})


message(STATUS "PROJECT_SOURCE_DIR = " ${PROJECT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/../../")

