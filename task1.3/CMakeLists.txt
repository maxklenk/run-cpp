cmake_minimum_required (VERSION 3.1)
project (Task1.3)
add_executable (validate_emails validate_emails.cpp)
target_compile_features(validate_emails PRIVATE cxx_range_for)