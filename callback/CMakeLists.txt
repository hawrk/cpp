cmake_minimum_required(VERSION 3.10)
project(callback1)

set(CXX_STANDARD 17)

add_executable(callback1 callback_main.cpp)
add_executable(callback2 callback2_main.cpp)
add_executable(callback3 callback3_main.cpp)

target_link_libraries(
    callback3
    pthread
)
