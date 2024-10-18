cmake_minimum_required(VERSION 3.10)
project(thread_class)

set(CMAKE_CXX_STANDARD 17)

#add_executable( thread_class.cpp)
add_executable(thread_notify thread_notify.cpp)
target_link_libraries(thread_notify pthread)