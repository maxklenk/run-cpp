cmake_minimum_required (VERSION 3.1)
project (Task5.1)
set (CMAKE_CXX_STANDARD 14)

# compile & link
add_library (ModuloCounter ModuloCounter.cpp)
add_executable (run test.cpp)
target_link_libraries (run ModuloCounter)

# test
#include(CTest)
#add_test (run-runs run)