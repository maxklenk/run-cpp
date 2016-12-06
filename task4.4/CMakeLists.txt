cmake_minimum_required (VERSION 3.1)
project (Task1.1)
set (CMAKE_CXX_STANDARD 14)

# compile & link
add_library (tea_filebuf tea_filebuf.cpp)
add_executable (run tea_filebuf-test.cpp)
target_link_libraries (run tea_filebuf)

# test
#include(CTest)
#add_test (run-runs run)