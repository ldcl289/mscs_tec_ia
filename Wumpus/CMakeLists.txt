cmake_minimum_required(VERSION 3.3)
project(Agent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Agent.cpp Agent.h Action.cpp Action.h Space.h Coordinate.cpp Coordinate.h BaseKnowledge.cpp BaseKnowledge.h)
add_executable(Agent ${SOURCE_FILES})