cmake_minimum_required(VERSION 3.10...4.0)
project(FallingSand CXX)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

add_executable(FallingSand 
    src/Main.cpp
    src/Grid.cpp
    src/Cell.cpp
    src/Game.cpp
    src/GUI.cpp
)
target_link_libraries(FallingSand raylib)
