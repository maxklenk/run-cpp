cmake_minimum_required (VERSION 3.1)
project (Task5.3)
set (CMAKE_CXX_STANDARD 14)

add_executable(seven dice.cpp player.cpp game.cpp seven-main.cpp)
add_executable(mud dice.cpp player.cpp game.cpp mud-main.cpp)

# test
#include(CTest)
#add_test (run-runs run)