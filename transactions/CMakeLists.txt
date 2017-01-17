cmake_minimum_required(VERSION 3.6)
project(transactions)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    main.cpp
    Transaction.cpp
    Transaction.h)

add_executable(transactions ${SOURCE_FILES})