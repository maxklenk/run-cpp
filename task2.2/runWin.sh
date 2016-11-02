#!/usr/bin/env sh

mkdir _build
cd _build
cmake ..
cmake --build .

Debug/businesscard_raytracer.exe > image.ppm