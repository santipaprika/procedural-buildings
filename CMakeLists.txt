cmake_minimum_required(VERSION 2.8)
project(procedural_buildings)

set(CMAKE_CXX_STANDARD 17)

include_directories(glm)

add_executable(procedural_buildings main.cpp Scope.cpp Scope.h Shape.h Rule.cpp Rule.h S.cpp S.h Context.cpp Context.h Grammar.cpp Grammar.h NonTerminalShape.cpp NonTerminalShape.h T.cpp T.h Pop.cpp Pop.h Push.cpp Push.cpp I.cpp I.h Mesh.cpp Mesh.h PLYWriter.cpp PLYWriter.h R.h R.cpp)

