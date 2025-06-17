/*
 * @Author: hawrkchen
 * @Date: 2025-06-16 13:33:42
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-17 11:31:07
 * @Description: 
 * @FilePath: /mqttrpc/main_client.cpp
 */


#include <iostream>

#include "mqtt/mqtt_rpc_client.hpp"

int main(int argc, char* argv[]) {

    MQTTRPCClient client("tcp://localhost:1883",
                        "robot_clientA",
                        "robot/request",       // 指定推送
                        "robot/response");   // 指定订阅
    
    client.start();

    client.send_request("get_status",
                        {{"msg", "hello timeout test"}},
                        [](const std::string& request_id, const nlohmann::json& response, bool is_timeout) {
                            if(is_timeout) {
                                std::cout << "Request timed out" << std::endl;
                            } else {
                                std::cout << "Response: " << response.dump() << std::endl;
                            }
                        },
                        2000, // timeout
                        true);

    // 不需要回执
    while(true) {
         client.send_request("log_event", 
                         {{"msg", "hello fire-and-forget"}},
                         nullptr, // callback
                         0, // timeout
                         false);
        std::this_thread::sleep_for(std::chrono::seconds(1));                
    }


    //std::this_thread::sleep_for(std::chrono::seconds(10));
    client.stop();
    return 0;
}