#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
cmake --build .

./businesscard_raytracer > image.ppm