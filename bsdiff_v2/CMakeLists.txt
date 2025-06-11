cmake_minimum_required(VERSION 3.10)
project(bsdiff_v2)

set(CMAKE_CXX_STANDARD 17)
# 设置输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(BSDIFF_SOURCE bsdiff/bsdiff.c)
set(BSPATCH_SOURCE bsdiff/bspatch.c)

#生成bsdiff 动态库
add_library(bsdiff SHARED ${BSDIFF_SOURCE} ${BSPATCH_SOURCE})

target_link_libraries(bsdiff bz2)

add_executable(bsdiff_offical bsdiff_offical.cpp)
add_executable(bspatch_offical bspatch_offical.cpp)

target_link_libraries(bsdiff_offical bsdiff)
target_link_libraries(bspatch_offical bsdiff)

