cmake_minimum_required(VERSION 3.10)
project(sqlite3)

set(CMAKE_CXX_STANDARD 17)


find_package(SQLite3 REQUIRED)
find_package(SqliteOrm REQUIRED)


add_executable(main sqlite3.cpp)

add_executable(sqlorm sqliteOrm.cpp)

target_link_libraries(sqlorm PUBLIC sqlite3)

target_link_libraries(main PUBLIC sqlite3)