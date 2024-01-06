#!/bin/bash

if [ "$#" -ne 2 ] && [ "$#" -ne 1 ]; then
  echo "Usage: $0 [-l/-c/-e] [file_number] -h for help"
  exit 1
fi

file_number=$2


case "$1" in
  -l)
    echo "Reading with nano..."
    nano "./test/exemple$file_number.algo"
    ;;
  -c)
    echo "Compiling..."
    ./bin/arc "./test/exemple$file_number.algo"
    ;;
  -e)
    echo "Executing Node.js command..."
    ./bin/arc "./test/exemple$file_number.algo"
    node ./ram/ram.js out.ram ./ram/input
    ;;
  -h)
    echo "List of examples..."
    cat  "./test/list_example.txt"
    ;;
  *)
    echo "Invalid option: $1. Use -l for reading, -c for compiling, -e for executing, or -h for help."
    exit 1
    ;;
esac

echo "Done"
