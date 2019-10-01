cmake_minimum_required(VERSION 3.0)

project(rooms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)
FetchContent_Declare(
    SDL2
    URL "https://www.libsdl.org/release/SDL2-2.0.10.tar.gz"
    URL_MD5 "5a2114f2a6f348bdab5bf52b994811db"
)

FetchContent_MakeAvailable(SDL2)

add_subdirectory(assets)
add_subdirectory(src)
