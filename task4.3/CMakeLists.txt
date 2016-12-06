cmake_minimum_required (VERSION 3.1)
project (Task1.1)
set (CMAKE_CXX_STANDARD 14)

# compile & link
add_library (tree_streambuf tree_streambuf.cpp)
add_executable (run tree_streambuf-test.cpp)
target_link_libraries (run tree_streambuf)

# test
#include(CTest)
#add_test (run-runs run)