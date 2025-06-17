/*
 * @Author: hawrkchen
 * @Date: 2025-06-16 13:31:11
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-16 16:42:54
 * @Description:  带请求响应和超时间的MQTT客户端
 * @FilePath: /mqttrpc/mqtt/mqtt_rpc_client.hpp
 */

#pragma once

#include <string>
#include <functional>
#include <map>
#include <mutex>
#include <atomic>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include <mqtt/async_client.h>

using MQTTResponseCallback = std::function<void(const std::string& request_id, 
                                                const nlohmann::json& response,
                                                bool is_timeout)>;

class MQTTRPCClient {
    public:
        MQTTRPCClient(const std::string& broker_url,
                     const std::string& client_id,
                     const std::string& request_topic,
                     const std::string& response_topic);

        ~MQTTRPCClient();

        void start();
        void stop();

        // 超时timeout_ms <= 0, fire-and-forget;  > 0, 等待响应或超时
        // need_reply = false, 只发送请求，服务端不会回执
        void send_request(const std::string& method,
                          const nlohmann::json& data, 
                          MQTTResponseCallback cb = nullptr,
                          int timeout_ms = 5000,
                          bool need_reply = true);

    private:
        struct PeddingRequest {
            MQTTResponseCallback cb;
            std::chrono::steady_clock::time_point deadline;
            bool responded;
        };

        std::string broker_url_;
        std::string client_id_;
        std::string request_topic_;
        std::string response_topic_;
        std::string username_;
        std::string password_;

        mqtt::async_client mqtt_client_;

        std::map<std::string, PeddingRequest> pending_requests_;
        std::mutex mutex_;
        std::thread timeout_thread_;
        std::atomic<bool> running_{false};

        std::string gen_uuid();

        void on_message(const mqtt::const_message_ptr& message);
        void subscribe(const std::string& topic);
        void publish(const std::string& topic, const nlohmann::json& data);

        void timeout_checker();    
};
