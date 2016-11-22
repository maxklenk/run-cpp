cmake_minimum_required (VERSION 3.1)
project (Task3.3)
set (CMAKE_CXX_STANDARD 14)

# compile & link
add_library (Graph Graph.cpp)
add_library (GraphFactory GraphFactory.cpp)
add_library (InstanceCounter InstanceCounter.cpp)

add_executable (graph-test graph-test.cpp)
target_link_libraries (graph-test Graph GraphFactory InstanceCounter)
