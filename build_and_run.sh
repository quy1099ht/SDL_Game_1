#!/bin/bash

# Compile all source files
mkdir -p bin/debug

g++ -c src/*.cpp -std=c++14 -g -Wall -m64 -I include -I C:/SDL2-w64/include
if [ $? -ne 0 ]; then
  echo "Compilation failed."
  exit 1
fi

# Link object files and create the executable
g++ *.o -o bin/debug/main -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
if [ $? -ne 0 ]; then
  echo "Linking failed."
  exit 1
fi

# Run the executable
start bin/debug/main