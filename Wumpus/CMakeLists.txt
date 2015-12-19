cmake_minimum_required(VERSION 3.3)
project(Agent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Agent.cpp Agent.h Action.cpp Action.h Space.h Coordinate.cpp Coordinate.h BaseKnowledge.cpp BaseKnowledge.h TreeSearch/ProblemRoute.cpp TreeSearch/ProblemRoute.h TreeSearch/AStar.cpp TreeSearch/AStar.h TreeSearch/TreeSearch.cpp TreeSearch/TreeSearch.h TreeSearch/Node.cpp TreeSearch/Node.h TreeSearch/Tree.cpp TreeSearch/Tree.h)
add_executable(Agent ${SOURCE_FILES})