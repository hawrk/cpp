cmake_minimum_required(VERSION 2.8)
project(pcl)

find_package(PCL REQUIRED)
include_directories("/usr/include/pcl-1.12/")
include_directories("/usr/include/eigen3/Eigen/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})
link_directories(${PCL_LIBRARY_DIRS})

add_executable(pcl_example main.cpp)

target_link_libraries(pcl_example ${PCL_LIBRARIES}) 
target_link_libraries(pcl_example usb)
