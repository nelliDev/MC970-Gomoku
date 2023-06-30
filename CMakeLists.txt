cmake_minimum_required(VERSION 3.9)

project(gomoku)

find_package(OpenMP REQUIRED)

set(CMAKE_C_STANDARD 99)

set_source_files_properties(src/game.cpp src/main.cpp src/player.cpp PROPERTIES COMPILE_OPTIONS "-g")

add_executable(main src/game.cpp src/main.cpp src/player.cpp)
