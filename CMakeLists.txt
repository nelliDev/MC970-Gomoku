cmake_minimum_required(VERSION 3.9)

project(gomoku)

find_package(OpenMP REQUIRED)

set(CMAKE_C_STANDARD 99)

set_source_files_properties(
    src/game.cpp
    src/play_vs_computer.cpp
    src/players/player_serial.cpp
    src/players/player_parallel_eval.cpp
    src/players/player_parallel_full.cpp
    src/players/player_parallel_minimax.cpp
    src/players/player_parallel_regex.cpp
    src/players/player_parallel_scores.cpp
    src/timming.cpp
    PROPERTIES COMPILE_OPTIONS "-g;-fopenmp"
)
add_executable(play_vs_computer src/game.cpp src/play_vs_computer.cpp src/players/player_parallel_full.cpp)
add_executable(serial src/game.cpp src/timming.cpp src/players/player_serial.cpp)
add_executable(parallel_eval src/game.cpp src/timming.cpp src/players/player_parallel_eval.cpp)
add_executable(parallel_full src/game.cpp src/timming.cpp src/players/player_parallel_full.cpp)
add_executable(parallel_minimax src/game.cpp src/timming.cpp src/players/player_parallel_minimax.cpp)
add_executable(parallel_regex src/game.cpp src/timming.cpp src/players/player_parallel_regex.cpp)
add_executable(parallel_scores src/game.cpp src/timming.cpp src/players/player_parallel_scores.cpp)

target_link_libraries(play_vs_computer PUBLIC OpenMP::OpenMP_C)

target_link_libraries(serial PUBLIC OpenMP::OpenMP_C)
target_link_libraries(parallel_eval PUBLIC OpenMP::OpenMP_C)
target_link_libraries(parallel_full PUBLIC OpenMP::OpenMP_C)
target_link_libraries(parallel_minimax PUBLIC OpenMP::OpenMP_C)
target_link_libraries(parallel_regex PUBLIC OpenMP::OpenMP_C)
target_link_libraries(parallel_scores PUBLIC OpenMP::OpenMP_C)