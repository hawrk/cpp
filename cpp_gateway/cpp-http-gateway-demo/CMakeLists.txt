project(cpp-http-gateway-demo)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

file(GLOB SOURCES
    src/*.cpp
    src/utils/*.cpp
)

add_executable(cpp-http-gateway-demo ${SOURCES})

find_package(Boost REQUIRED COMPONENTS system)
target_link_libraries(cpp-http-gateway-demo Boost::system)