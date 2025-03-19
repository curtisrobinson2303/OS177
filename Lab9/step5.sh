#!/bin/bash
# Name: Curtis Robinson (converted version)
# Description: This script copies an input file into multiple output files concurrently using dd.
#              It takes three arguments:
#                1. filename    - the file to copy.
#                2. buffer_size - the block size (in bytes) for dd.
#                3. num_threads - the number of concurrent copy operations.
#
# Usage: ./script.sh filename buffer_size num_threads

# Check that three arguments are provided.
if [ "$#" -lt 3 ]; then
  echo "Usage: $0 filename buffer_size num_threads" >&2
  exit 1
fi

filename="$1"
buffer_size="$2"
num_threads="$3"

# Validate that buffer_size and num_threads are positive integers.
if ! [[ "$buffer_size" =~ ^[1-9][0-9]*$ ]]; then
  echo "Invalid buffer size" >&2
  exit 1
fi

if ! [[ "$num_threads" =~ ^[1-9][0-9]*$ ]]; then
  echo "Invalid number of threads" >&2
  exit 1
fi

# Verify that the input file exists and is readable.
if [ ! -r "$filename" ]; then
  echo "Error: Cannot read file $filename" >&2
  exit 1
fi

# Array to store background process IDs.
pids=()

# Launch concurrent copy operations.
for (( i=0; i<num_threads; i++ )); do
  output_file="copy${i}.out"
  # Start dd in the background; status=none suppresses output.
  dd if="$filename" of="$output_file" bs="$buffer_size" status=none &
  pid=$!
  pids+=("$pid")
  echo "Started copying to $output_file in background (PID $pid)."
done

# Wait for all background processes and check for errors.
errors=0
for pid in "${pids[@]}"; do
  if ! wait "$pid"; then
    echo "A copy process with PID $pid failed." >&2
    (( errors++ ))
  fi
done

if [ "$errors" -gt 0 ]; then
  echo "One or more copy operations failed." >&2
  exit 1
fi

exit 0
