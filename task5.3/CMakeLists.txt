cmake_minimum_required (VERSION 3.1)
project (Task5.3)
set (CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES dice.cpp player.cpp game.cpp seven-main.cpp)
add_executable(run ${SOURCE_FILES})

# test
#include(CTest)
#add_test (run-runs run)