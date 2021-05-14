cmake_minimum_required(VERSION 2.8)
project(procedural_buildings)

set(CMAKE_CXX_STANDARD 17)

include_directories(glm)

add_executable(procedural_buildings main.cpp Scope.cpp Scope.h)

