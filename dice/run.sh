#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
cmake --build .
./seven 4 10
./mud 4 10