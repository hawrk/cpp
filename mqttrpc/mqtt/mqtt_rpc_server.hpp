/*
 * @Author: hawrkchen
 * @Date: 2025-06-16 13:32:51
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-17 10:39:45
 * @Description: 
 * @FilePath: /mqttrpc/mqtt/mqtt_rpc_server.hpp
 */

#pragma once

#include <string>
#include <functional>
#include <map>
#include <nlohmann/json.hpp>

#include <mqtt/async_client.h>

using MQTTRequestHandle = std::function<nlohmann::json(const nlohmann::json&)>;

class MQTTRPCServer {
    public:
        MQTTRPCServer(const std::string& broker_url,
                      const std::string& server_id,
                      const std::string& request_topic);

        ~MQTTRPCServer();

        void start();
        void stop();
        
        // 注册method处理器
        void register_method_handler(const std::string& method, 
                                    MQTTRequestHandle handler);

    private:
        std::string broker_url_;
        std::string server_id_;
        std::string request_topic_;

        mqtt::async_client mqtt_server_;
        std::map<std::string, MQTTRequestHandle> method_handlers_;    // key： 业务类型 ， val: 处理函数

        void on_message(const mqtt::const_message_ptr& message);
        void subscribe(const std::string& topic);
        void publish(const std::string& topic, const nlohmann::json& payload);
};