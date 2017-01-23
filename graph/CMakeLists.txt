cmake_minimum_required(VERSION 3.6)
project(graph)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Graph.h
        main.cpp)

add_executable(graph ${SOURCE_FILES})