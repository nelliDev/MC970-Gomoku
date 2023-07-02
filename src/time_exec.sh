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

# Function to calculate standard deviation
calculate_stddev() {
  sum=0
  for time in "${@:2}"; do
    sum=$(awk -v sum="$sum" -v time="$time" 'BEGIN {printf "%.6f", sum + time}')
  done
  average=$(awk -v sum="$sum" -v count="$1" 'BEGIN {printf "%.6f", sum / count}')

  diff_sum=0
  for time in "${@:2}"; do
    diff=$(awk -v average="$average" -v time="$time" 'BEGIN {printf "%.6f", time - average}')
    diff_sq=$(awk -v diff="$diff" 'BEGIN {printf "%.6f", diff * diff}')
    diff_sum=$(awk -v diff_sum="$diff_sum" -v diff_sq="$diff_sq" 'BEGIN {printf "%.6f", diff_sum + diff_sq}')
  done

  variance=$(awk -v diff_sum="$diff_sum" -v count="$1" 'BEGIN {printf "%.6f", diff_sum / count}')
  stddev=$(awk -v variance="$variance" 'BEGIN {printf "%.6f", sqrt(variance)}')
  echo "$stddev"
}

# Redirect output to /dev/null
exec_with_silent_output() {
  "$@" > /dev/null 2>&1
}

# Declare arrays for storing average times, standard deviations, and speedups
average_times=()
standard_deviations=()
speedups=()

# Iterate through each executable
for executable in "${executables[@]}"; do
  execution_times=()
  echo "Running $executable..."

  # Run the executable five times
  for ((i=1; i<=5; i++)); do
    start_time=$(date +%s.%N)
    exec_with_silent_output ./$executable
    end_time=$(date +%s.%N)
    execution_time=$(awk -v start="$start_time" -v end="$end_time" 'BEGIN {printf "%.6f", end - start}')
    execution_times+=($execution_time)
    echo "Run $i completed in $execution_time seconds"
  done

  # Calculate and display the average execution time
  average_time=$(calculate_average 5 "${execution_times[@]}")
  average_times+=($average_time)

  # Calculate and display the standard deviation
  stddev=$(calculate_stddev 5 "${execution_times[@]}")
  standard_deviations+=($stddev)

  echo "Average execution time for 5 runs of $executable: $average_time seconds"
  echo "Standard deviation for 5 runs of $executable: $stddev seconds"
  echo

done

# Calculate speedups
for ((i=0; i<${#executables[@]}-1; i++)); do
  speedup=$(awk -v serial_time="${average_times[-1]}" -v parallel_time="${average_times[i]}" 'BEGIN {printf "%.6f", serial_time / parallel_time}')
  speedups+=($speedup)
done

# Determine the maximum widths for each column
max_executable_width=0
max_avg_time_width=0
max_stddev_width=0
max_speedup_width=0

for ((i=0; i<${#executables[@]}-1; i++)); do
  executable_width=${#executables[i]}

  if ((executable_width > max_executable_width)); then
    max_executable_width=$executable_width
  fi

  avg_time_width=${#average_times[i]}
  stddev_width=${#standard_deviations[i]}
  speedup_width=${#speedups[i]}

  if ((avg_time_width > max_avg_time_width)); then
    max_avg_time_width=$avg_time_width
  fi

  if ((stddev_width > max_stddev_width)); then
    max_stddev_width=$stddev_width
  fi

  if ((speedup_width > max_speedup_width)); then
    max_speedup_width=$speedup_width
  fi
done

serial_time_width=${#average_times[-1]}
serial_stddev_width=${#standard_deviations[-1]}

# Print table
echo "-----------------------------------------------------------------"
printf "| %-19s | %-12s | %-11s | %-10s |\n" "Executable" "Avg Time (s)" "Std Dev (s)" "Speedup"
echo "-----------------------------------------------------------------"
for ((i=0; i<${#executables[@]}-1; i++)); do
  printf "| %-19s | %-12s | %-11s | %-10s |\n" "${executables[i]##*/}" "${average_times[i]}" "${standard_deviations[i]}" "${speedups[i]}"
done
echo "-----------------------------------------------------------------"
printf "| %-19s | %-12s | %-11s | %-10s |\n" "serial" "${average_times[-1]}" "${standard_deviations[-1]}" "-"
echo "-----------------------------------------------------------------"
