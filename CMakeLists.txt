cmake_minimum_required(VERSION 3.6)
project(assignment7)

set(CMAKE_CXX_STANDARD 14)

set(TEMPLATEREF_FILES
        assignment7/template-refactoring/ISBN.h
        assignment7/template-refactoring/main.cpp)

add_executable(template-refactoring ${TEMPLATEREF_FILES})

set(COLLECT_FILES
        assignment7/collect/collect.h
        assignment7/collect/main.cpp)

add_executable(collect ${COLLECT_FILES})

set(SIGNAL_FILES
        assignment7/signal/main.cpp
        assignment7/signal/Signal.h)

add_executable(signal ${SIGNAL_FILES})

set(VARIANT_FILES
        assignment7/variant/main.cpp
        assignment7/variant/Variant.h)

add_executable(variant ${VARIANT_FILES})

