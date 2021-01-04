cmake_minimum_required(VERSION 3.2)
project(MaxCut)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(algorithms)
add_subdirectory(testing)