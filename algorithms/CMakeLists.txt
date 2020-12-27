cmake_minimum_required(VERSION 3.2)
project(MaxCutLib)

set(CMAKE_CXX_STANDARD 20)

add_library(MaxCutLib STATIC
            impl/base/graph.cpp
            impl/base/maxcut.cpp
            impl/base/iterating.cpp
            impl/bruteforce/bruteforce.cpp)

set_target_properties(MaxCutLib PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/"
                      )

target_include_directories(MaxCutLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
