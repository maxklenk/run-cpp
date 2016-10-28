#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
cmake --build .

Debug/count_words.exe
Debug/count_words.exe 8
