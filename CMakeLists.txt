cmake_minimum_required(VERSION 3.0)

project(rooms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)
FetchContent_Declare(
    SDL2
    URL "https://www.libsdl.org/release/SDL2-2.0.12.tar.gz"
    URL_MD5 "783b6f2df8ff02b19bb5ce492b99c8ff"
)

FetchContent_MakeAvailable(SDL2)

add_subdirectory(assets)
add_subdirectory(src)
