cmake_minimum_required (VERSION 3.1)
project (Task5.4)
set (CMAKE_CXX_STANDARD 14)

# compile & link
#add_library (Lib Lib.cpp)
add_executable (run syntax.cpp)
#target_link_libraries (run Lib)

# test
#include(CTest)
#add_test (run-runs run)