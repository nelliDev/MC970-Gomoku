#!/bin/bash

# Array of executables
executables=(
    "../build/parallel_eval"
    "../build/parallel_full"
    "../build/parallel_minimax"
    "../build/parallel_regex"
    "../build/parallel_scores"
    "../build/parallel_hashing"
    "../build/serial_hashing"
    "../build/serial"
)

# Function to calculate average execution time
calculate_average() {
  sum=0
  for time in "${@:2}"; do
    sum=$(awk -v sum="$sum" -v time="$time" 'BEGIN {printf "%.6f", sum + time}')
  done
  average=$(awk -v sum="$sum" -v count="$1" 'BEGIN {printf "%.6f", sum / count}')
  echo "$average"
}

# Redirect output to /dev/null
exec_with_silent_output() {
  "$@" > /dev/null 2>&1
}

# Declare arrays for storing average times and speedups
average_times=()
speedups=()

# Iterate through each executable
for executable in "${executables[@]}"; do
  execution_times=()
  echo "Running $executable..."
  
  # Run the executable three times
  for ((i=1; i<=3; i++)); do
    start_time=$(date +%s.%N)
    exec_with_silent_output ./$executable
    end_time=$(date +%s.%N)
    execution_time=$(awk -v start="$start_time" -v end="$end_time" 'BEGIN {printf "%.6f", end - start}')
    execution_times+=($execution_time)
    echo "Run $i completed in $execution_time seconds"
  done
  
  # Calculate and display the average execution time
  average_time=$(calculate_average 3 "${execution_times[@]}")
  average_times+=($average_time)
  echo "Average execution time for 3 runs of $executable: $average_time seconds"
  echo
  
done

# Calculate speedups
for ((i=0; i<${#executables[@]}; i++)); do
  speedup=$(awk -v serial_time="${average_times[-1]}" -v parallel_time="${average_times[i]}" 'BEGIN {printf "%.6f", serial_time / parallel_time}')
  speedups+=($speedup)
done

# Print table
echo "-----------------------------------------------------------"
echo "| Executable         | Avg Time (s) | Speedup              |"
echo "-----------------------------------------------------------"
for ((i=0; i<${#executables[@]}; i++)); do
  printf "| %-19s | %-12s | %-19s |\n" "${executables[i]##*/}" "${average_times[i]}" "${speedups[i]}"
done
echo "-----------------------------------------------------------"
