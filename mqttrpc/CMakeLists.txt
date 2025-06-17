
cmake_minimum_required(VERSION 3.10)
project(mqttrpc)

set(CMAKE_CXX_STANDARD 17)

add_executable(mqttrpc_server main_server.cpp mqtt/mqtt_rpc_server.cpp)

add_executable(mqttrpc_client main_client.cpp mqtt/mqtt_rpc_client.cpp)

target_link_libraries(mqttrpc_server paho-mqttpp3 paho-mqtt3a uuid)
target_link_libraries(mqttrpc_client paho-mqttpp3 paho-mqtt3a uuid)