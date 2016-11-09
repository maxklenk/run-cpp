cmake_minimum_required (VERSION 3.1)
project (Task2.2)
set (CMAKE_CXX_STANDARD 14)

# compile
add_executable (businesscard_raytracer businesscard_raytracer.cpp)
target_compile_features(businesscard_raytracer PRIVATE cxx_range_for)

# test
include(CTest)
add_test (businesscard_raytracer_runs businesscard_raytracer)