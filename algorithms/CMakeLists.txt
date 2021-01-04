cmake_minimum_required(VERSION 3.2)
project(MaxCutLib)

set(CMAKE_CXX_STANDARD 20)

add_library(MaxCutLib STATIC
            impl/base/graph.cpp
            impl/base/maxcut.cpp
            impl/base/iterating.cpp
            impl/bruteforce/bruteforce.cpp
            impl/half-optimal/half-optimal.cpp
            impl/goemans-williamson/goemans-williamson.cpp)

set_target_properties(MaxCutLib PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/"
                      )

target_include_directories(MaxCutLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(MOSEK_DIR "$ENV{HOME}/mosek/9.2")
find_package(MOSEK REQUIRED)

target_include_directories(MaxCutLib PRIVATE ${MOSEK_INCLUDE_DIR})
target_link_libraries(MaxCutLib ${MOSEK_LIBRARIES})
string(REPLACE "libmosek" "libfusion" FUSION_LIBRARIES ${MOSEK_LIBRARIES})
target_link_libraries(MaxCutLib ${FUSION_LIBRARIES})