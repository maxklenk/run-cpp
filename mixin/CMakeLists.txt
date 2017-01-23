cmake_minimum_required(VERSION 3.6)
project(mixin)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        BezierCurve.cpp
        BezierCurve.h
        Cached.h
        Circle.cpp
        Circle.h
        main.cpp)

add_executable(mixin ${SOURCE_FILES})