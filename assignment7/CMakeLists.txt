cmake_minimum_required(VERSION 3.6)
project(assignment7)

set(CMAKE_CXX_STANDARD 14)

set(TEMPLATEREF_FILES
        template-refactoring/ISBN.h
        template-refactoring/main.cpp)

add_executable(template-refactoring ${TEMPLATEREF_FILES})

set(COLLECT_FILES
        collect/collect.h
        collect/main.cpp)

add_executable(collect ${COLLECT_FILES})

set(SIGNAL_FILES
        signal/main.cpp
        signal/Signal.h)

add_executable(signal ${SIGNAL_FILES})

set(VARIANT_FILES
        variant/main.cpp
        variant/Variant.h)

add_executable(variant ${VARIANT_FILES})

