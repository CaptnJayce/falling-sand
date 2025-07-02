cmake_minimum_required(VERSION 3.10)
project(FallingSand CXX)

if(CMAKE_CROSSCOMPILING OR WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
endif()

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static library" FORCE)
FetchContent_MakeAvailable(raylib)

add_executable(FallingSand 
    src/Main.cpp
    src/Grid.cpp
    src/Cell.cpp
    src/Game.cpp
)

target_link_libraries(FallingSand PRIVATE raylib)

if(MINGW)
    target_link_libraries(FallingSand PRIVATE
        -static
        -lwinmm
        -lgdi32
        -lopengl32
    )
endif()
