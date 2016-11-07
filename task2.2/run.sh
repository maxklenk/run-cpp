#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
rm image.ppm
cmake --build . && ./businesscard_raytracer > image.ppm