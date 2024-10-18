cmake_minimum_required(VERSION 3.8)
project(opencv)

add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(opencv main.cpp)

target_link_libraries(opencv ${OpenCV_LIBS})