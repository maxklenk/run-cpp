cmake_minimum_required (VERSION 3.1)
project (Task5.3)
set (CMAKE_CXX_STANDARD 14)

# compile & link
#add_library (Lib Lib.cpp)
set(SOURCE_FILES seven-main.cpp)
add_executable(run ${SOURCE_FILES})
#target_link_libraries (run Lib)

# test
#include(CTest)
#add_test (run-runs run)