cmake_minimum_required (VERSION 3.1)
project (Task2.1)
add_executable (montecarlopi montecarlopi.cpp)
target_compile_features(montecarlopi PRIVATE cxx_range_for)