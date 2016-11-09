#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
#cmake --build . && ctest .
rm image.ppm
cmake --build . && ./businesscard_raytracer > image.ppm
#cmake --build . && ./businesscard_raytracer