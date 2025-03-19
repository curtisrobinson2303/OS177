#!/bin/bash
# Name: Curtis Robinson (converted version)
# Description: This script reads an input file in blocks of a specified size and writes its content
#              to a new file called copy.out.
# Usage: ./script.sh filename buffer_size

# Check that two arguments are provided.
if [ "$#" -lt 2 ]; then
  echo "Usage: $0 filename buffer_size" >&2
  exit 1
fi

input="$1"
bufSize="$2"

# Validate that the buffer size is a positive integer.
if ! [[ "$bufSize" =~ ^[1-9][0-9]*$ ]]; then
  echo "Invalid buffer size" >&2
  exit 1
fi

# Verify that the input file exists and is readable.
if [ ! -r "$input" ]; then
  echo "Error: Cannot read file $input" >&2
  exit 1
fi

# Use dd to copy the file in blocks of the specified buffer size to copy.out.
if ! dd if="$input" of="copy.out" bs="$bufSize" status=none; then
  echo "Error occurred during copying" >&2
  exit 1
fi

exit 0
