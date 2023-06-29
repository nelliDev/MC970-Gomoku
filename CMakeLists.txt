cmake_minimum_required(VERSION 3.9)

project(gomoku)

find_package(OpenMP REQUIRED)

set(CMAKE_C_STANDARD 99)

add_executable(main src/game.cpp src/main.cpp)
