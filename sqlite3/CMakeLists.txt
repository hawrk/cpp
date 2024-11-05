cmake_minimum_required(VERSION 3.10)
project(sqlite3)

set(CMAKE_CXX_STANDARD 17)

add_executable(main sqlite3.cpp)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main PUBLIC sqlite3)