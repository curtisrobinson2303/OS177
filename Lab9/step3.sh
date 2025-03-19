#!/bin/bash
# Name: Curtis Robinson (converted version)
# Description: This script measures I/O performance by reading a file using a user-specified
#              buffer size. It reads the file in blocks of the given size and discards the output.
# Usage: ./script.sh filename buffer_size

# Check that two arguments are provided.
if [ "$#" -lt 2 ]; then
  echo "Usage: $0 filename buffer_size" >&2
  exit 1
fi

file="$1"
bufSize="$2"

# Validate that the buffer size is a positive integer.
if ! [[ "$bufSize" =~ ^[1-9][0-9]*$ ]]; then
  echo "Invalid buffer size" >&2
  exit 1
fi

# Verify the file exists and is readable.
if [ ! -r "$file" ]; then
  echo "Error: Cannot read file $file" >&2
  exit 1
fi

# Use dd to read the file in blocks of the specified buffer size, discarding the output.
dd if="$file" of=/dev/null bs="$bufSize" status=none

exit 0
