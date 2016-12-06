cmake_minimum_required (VERSION 3.1)
project (Task1.1)
set (CMAKE_CXX_STANDARD 14)

# compile & link
add_library (Player player.cpp)
add_library (ipc_player ipc_player.cpp)
add_library (ipc_viewer ipc_viewer.cpp)
add_executable (run viewer.cpp)
target_link_libraries (run Player ipc_player ipc_viewer)

# test
#include(CTest)
#add_test (run-runs run)