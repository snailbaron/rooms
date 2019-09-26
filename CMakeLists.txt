cmake_minimum_required(VERSION 3.0)

project(rooms)

find_package(SDL2 REQUIRED COMPONENTS SDL2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(src)
