cmake_minimum_required(VERSION 3.10)
project(usb_detect)

add_executable(usb_detect main.cpp) 

target_link_libraries(usb_detect udev)