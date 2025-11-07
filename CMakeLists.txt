cmake_minimum_required(VERSION 3.10)
project(AirportPathfinder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pathfinder
    src/main.cpp
    src/Graph.cpp
    src/Dijkstra.cpp
)

target_include_directories(pathfinder PRIVATE src)