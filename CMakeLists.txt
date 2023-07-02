cmake_minimum_required(VERSION 3.9)

project(gomoku)

find_package(OpenMP REQUIRED)

set(CMAKE_C_STANDARD 99)

set_source_files_properties(src/game.cpp src/main.cpp src/player.cpp src/player_parallel.cpp src/timming.cpp PROPERTIES COMPILE_OPTIONS "-g;-fopenmp")

add_executable(main src/game.cpp src/main.cpp src/player.cpp)
add_executable(main_parallel src/game.cpp src/main.cpp src/player_parallel.cpp)
add_executable(timming_parallel src/game.cpp src/timming.cpp src/player_parallel.cpp)
add_executable(timming src/game.cpp src/timming.cpp src/player.cpp)

target_link_libraries(timming_parallel
    PUBLIC OpenMP::OpenMP_C)

target_link_libraries(main_parallel
    PUBLIC OpenMP::OpenMP_C)