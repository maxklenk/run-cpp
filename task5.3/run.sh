#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
cmake --build . && ./seven 4 1000 && ./mud 4 1000