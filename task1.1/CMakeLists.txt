cmake_minimum_required (VERSION 3.1)
project (Task1.1)
add_executable (greet_world greet_world.cpp)
target_compile_features(greet_world PRIVATE cxx_range_for)