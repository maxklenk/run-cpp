cmake_minimum_required(VERSION 3.6)
project(task3_1)

# $ brew install qt5
set(CMAKE_CXX_STANDARD 14)
set(Qt5Widgets_DIR "/usr/local/Cellar/qt5/5.7.0/lib/cmake/Qt5Widgets")

set(PARTICLE_SYSTEM
        main.cpp
        engine.cpp
        particle.cpp
        widget.cpp)

find_package(Qt5Widgets)
add_executable(particles ${PARTICLE_SYSTEM})
target_link_libraries(particles Qt5::Widgets)