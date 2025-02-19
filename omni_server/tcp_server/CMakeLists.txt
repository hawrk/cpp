cmake_minimum_required(VERSION 3.10)
project(tcp_server)

add_compile_options(-Wall -O2)

set(CMAKE_CXX_STANDARD 17)

add_executable(main_server main_server.cpp tcp_server.cpp)
target_link_libraries(main_server PUBLIC hv)


add_executable(main_client_loop main_client_loop.cpp)
target_link_libraries(main_client_loop PUBLIC hv)

add_executable(main_client main_client.cpp)
target_link_libraries(main_client PUBLIC hv)