#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
cmake --build .

./count_words
./count_words 8
