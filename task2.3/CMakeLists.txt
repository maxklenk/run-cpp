cmake_minimum_required (VERSION 3.1)
project (Task2.3)
set (CMAKE_CXX_STANDARD 14)

# compile & link
add_library (Value Value.cpp)
add_library (FileContent FileContent.cpp)
add_library (binaryfileformat binaryfileformat.cpp)
add_library (textfileformat textfileformat.cpp)
add_library (fileformat-testdata fileformat-testdata.cpp)

add_executable (fileformat-test fileformat-test.cpp)
target_link_libraries (fileformat-test Value FileContent binaryfileformat textfileformat fileformat-testdata)

# test
include(CTest)
add_test (fileformat-test-runs fileformat-test)