cmake_minimum_required(VERSION 3.6)
project(imbang)

set(CMAKE_CXX_STANDARD 11)

set(OpenCV_DIR ~/opencv-3.1.0/build)
FIND_PACKAGE(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp imbang.cpp imbang.h tinyxml2.cpp tinyxml2.h)
add_executable(imbang ${SOURCE_FILES})

target_link_libraries(imbang ${OpenCV_LIBS})

