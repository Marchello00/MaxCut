cmake_minimum_required(VERSION 3.2)
project(MaxCutTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(MaxCutTest main.cpp)
target_link_libraries(MaxCutTest PUBLIC MaxCutLib)