cmake_minimum_required (VERSION 3.1)
project (Task2.3)

add_library (Value Value.cpp)
add_library (FileContent FileContent.cpp)
add_library (binaryfileformat binaryfileformat.cpp)
add_library (textfileformat textfileformat.cpp)
add_library (fileformat-testdata fileformat-testdata.cpp)

add_executable (fileformat-test fileformat-test.cpp)

target_link_libraries (fileformat-test LINK_PUBLIC Value)
target_link_libraries (fileformat-test LINK_PUBLIC FileContent)
target_link_libraries (fileformat-test LINK_PUBLIC binaryfileformat)
target_link_libraries (fileformat-test LINK_PUBLIC textfileformat)
target_link_libraries (fileformat-test LINK_PUBLIC fileformat-testdata)

set_property(TARGET Value PROPERTY CXX_STANDARD 14)
set_property(TARGET FileContent PROPERTY CXX_STANDARD 14)
set_property(TARGET binaryfileformat PROPERTY CXX_STANDARD 14)
set_property(TARGET textfileformat PROPERTY CXX_STANDARD 14)
set_property(TARGET fileformat-testdata PROPERTY CXX_STANDARD 14)
set_property(TARGET fileformat-test PROPERTY CXX_STANDARD 14)
