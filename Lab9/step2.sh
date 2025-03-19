#!/bin/bash
# Name: Curtis Robinson (converted version)
# Description: This script reads all the content from a file in 10,000-byte blocks
#              and (when run with the time command) measures how long it takes.

if [ "$#" -lt 1 ]; then
  echo "Usage: $0 filename" >&2
  exit 1
fi

file="$1"

if [ ! -r "$file" ]; then
  echo "Error: Cannot read file $file" >&2
  exit 1
fi

# Use dd to read the file in blocks of 10000 bytes, discarding the output.
# Running the script with 'time' (e.g., time ./script.sh file.txt) will measure the duration.
dd if="$file" of=/dev/null bs=10000 status=none

exit 0
