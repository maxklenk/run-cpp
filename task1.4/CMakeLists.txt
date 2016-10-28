cmake_minimum_required (VERSION 3.1)
project (Task1.4)
add_executable (count_words count_words.cpp)
target_compile_features(count_words PRIVATE cxx_range_for)