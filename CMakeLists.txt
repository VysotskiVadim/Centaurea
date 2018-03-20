cmake_minimum_required(VERSION 2.8)

project(centaurea)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_BUILD_TYPE Debug)
add_executable(centaurea src/main.cpp)
target_link_libraries(centaurea ${SDL2_LIBRARIES})