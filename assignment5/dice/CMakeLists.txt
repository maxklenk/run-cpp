cmake_minimum_required(VERSION 3.6)
project(dice)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES seven-main.cpp dice.h dice.cpp player.cpp player.h Game.cpp Game.h)
add_executable(dice ${SOURCE_FILES})