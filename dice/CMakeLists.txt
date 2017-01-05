cmake_minimum_required (VERSION 3.1)
project (Task5.3)
set (CMAKE_CXX_STANDARD 14)

add_library (lib dice.cpp player.cpp game.cpp )


add_executable(seven seven-main.cpp)
target_link_libraries (seven lib)
add_executable(mud mud-main.cpp)
target_link_libraries (mud lib)

# test
#include(CTest)
#add_test (run-runs run)