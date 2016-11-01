cmake_minimum_required (VERSION 3.1)
project (Task1.2)

# build lib
add_library (provider provider.cpp)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (provider PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (providerlibtest providerlibtest.cpp)

# Link the executable to the library. Since the library has
# public include directories we will use those link directories when building.
target_link_libraries (providerlibtest LINK_PUBLIC provider)


target_compile_features(provider PRIVATE cxx_range_for)
target_compile_features(providerlibtest PRIVATE cxx_range_for)