cmake_minimum_required(VERSION 3.2)
project(MaxCutTestGen)

set(CMAKE_CXX_STANDARD 20)

add_executable(RandomGraphGenerator random_graph.cpp)
add_executable(LargeCutGenerator large_cut.cpp)