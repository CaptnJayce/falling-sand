cmake_minimum_required(VERSION 3.10)
project(FallingSand CXX)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

add_executable(FallingSand main.cpp)
target_link_libraries(FallingSand raylib)
