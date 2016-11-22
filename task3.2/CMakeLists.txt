cmake_minimum_required(VERSION 3.6)
project(task3_2)
set (CMAKE_CXX_STANDARD 14)

add_library(externallibrary-x64.so SHARED IMPORTED)
set_target_properties(externallibrary PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/res/ )

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/res)
TARGET_LINK_LIBRARIES(externallibrary-x64.so)

set(SOURCE_FILES runner.cpp)
add_executable(task3_2 ${SOURCE_FILES})
