# Parallel Gomoku Players

This repository contains parallel implementations of Gomoku players for performance testing purposes. The codebase is organized as follows:

## Directory Structure

- **src/players**: This directory contains different implementations of Gomoku players with various parts of the code parallelized for testing purposes. Each file represents a different parallelization strategy. The following files are included:

  - `player_parallel_eval.cpp`: Parallelized evaluation function.
  - `player_parallel_full.cpp`: Full code parallelization implementation.
  - `player_parallel_hashing.cpp`: Full code parallelization implementation with hashing.
  - `player_parallel_minimax.cpp`: Parallelized minimax function.
  - `player_parallel_regex.cpp`: Parallelized regex function.
  - `player_parallel_scores.cpp`: Parallelized scores function.
  - `player_serial_hashing.cpp`: Serial implementation with hashing.
  - `player_serial_hashing.cpp`: Serial implementation.

- **src**: This directory contains additional source files related to the Gomoku game:

  - `game.cpp`: Controls the Gomoku game, displays the board, and checks for victory conditions.
  - `hashing.cpp`: Responsible for hashing.
  - `play_vs_computer.cpp`: Allows playing against a computer player.
  - `timing.cpp`: Simulates bot vs. bot matches for a specified number of rounds.
  - `time_exec.sh`: Executes and times all players in `timing.cpp`, generating a table with average times and speedup.

## Project Objectives

The main objectives of this project are:

1. **Performance Testing**: The parallel Gomoku players in the `src/players` directory explore different parallelization strategies to improve the performance of the Gomoku game-playing algorithms. By implementing parallelization techniques, we aim to speed up the decision-making process of the Gomoku players.

2. **Evaluation and Comparison**: The different parallelization strategies implemented in the players allow us to evaluate and compare their performance in terms of execution time and potential speedup achieved. The `timing.cpp` program simulates bot vs. bot matches to gather performance metrics, and the `time_exec.sh` script automates the execution and timing process, generating a table with average times and speedup values.

## Usage

To build and run the Gomoku players, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/nelliDev/MC970-Gomoku.git
   cd parallel-gomoku-players
   ```

2. Build the players:

   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. Run the game against a computer player:

   ```bash
   ./play_vs_computer
   ```

4. Simulate bot vs. bot matches:

   ```bash
   ./your_desired_algorithm
   ```

   The `time_exec.sh` script will execute and time all players in `timing.cpp`, generating a table in the terminal with average times and speedup.
