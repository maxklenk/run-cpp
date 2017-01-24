cmake_minimum_required(VERSION 3.6)
project(assignment6)

set(CMAKE_CXX_STANDARD 14)

set(GRAPH_FILES
        graph/Graph.h
        graph/main.cpp)

add_executable(graph_ ${GRAPH_FILES})

set(MIXIN_FILES
        mixin/BezierCurve.cpp
        mixin/BezierCurve.h
        mixin/Cached.h
        mixin/Circle.cpp
        mixin/Circle.h
        mixin/main.cpp)

add_executable(mixin_ ${MIXIN_FILES})

set(TRANSACTION_FILES
        transactions/main.cpp
        transactions/Transaction.cpp
        transactions/Transaction.h)

add_executable(transaction_ ${TRANSACTION_FILES})