cmake_minimum_required(VERSION 3.10)
project(test)

add_compile_options(-Wall -O2)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_thread_pool_complex test_thread_pool_complex.cpp ${SRC_LIST})
