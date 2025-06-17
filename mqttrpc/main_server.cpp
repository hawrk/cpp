/*
 * @Author: hawrkchen
 * @Date: 2025-06-16 13:33:50
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-17 10:17:25
 * @Description: 
 * @FilePath: /mqttrpc/main_server.cpp
 */

#include <iostream>

#include "mqtt/mqtt_rpc_server.hpp"

int main(int argc, char* argv[]) {
    MQTTRPCServer server("tcp://localhost:1883",
    "robot_server",
    "robot/request");

    server.start();

    // 接收需要回执的请求
    server.register_method_handler("get_status", [](const nlohmann::json& request) {
        std::cout << "on logic :Received request: " << request.dump() << std::endl;
        // 具体逻辑处理
        nlohmann::json response = {{"status", "ok"}};
        return response;
    });

    // 接收不需要回执的请求
    server.register_method_handler("log_event", [](const nlohmann::json& request) {
        std::cout << "Received request: " << request.dump() << std::endl;
        // 具体逻辑处理
        // 不需要回执的，直接处理完成
        // 理论上不会走到这一步
        return nlohmann::json();
    });

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    server.stop();
    return 0;
}

