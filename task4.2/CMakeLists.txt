cmake_minimum_required (VERSION 3.1)
project (Task1.1)
set (CMAKE_CXX_STANDARD 14)

find_package(Boost 1.62.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# compile & link
add_library (ipc_player ipc_player.cpp)
add_library (ipc_viewer ipc_viewer.cpp)

add_executable (runV viewer.cpp)
target_link_libraries (runV ipc_viewer)

add_executable (runP player.cpp)
target_link_libraries (runP ipc_player)

# test
#include(CTest)
#add_test (run-runs run)