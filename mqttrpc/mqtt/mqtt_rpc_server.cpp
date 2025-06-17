/*
 * @Author: hawrkchen
 * @Date: 2025-06-16 13:33:00
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-17 11:22:32
 * @Description: 
 * @FilePath: /mqttrpc/mqtt/mqtt_rpc_server.cpp
 */

#include "mqtt_rpc_server.hpp"

#include <iostream>

MQTTRPCServer::MQTTRPCServer(const std::string& broker_url, const std::string& server_id, const std::string& request_topic)
    : broker_url_(broker_url),
      server_id_(server_id),
      request_topic_(request_topic),
      mqtt_server_(broker_url, server_id) {

        mqtt_server_.set_message_callback([this](const mqtt::const_message_ptr& message) {
            this->on_message(message);
        });
}

MQTTRPCServer::~MQTTRPCServer() {
    this->stop();
}

void MQTTRPCServer::start() {
    std::cout << "Starting MQTT RPC server..." << std::endl;
    mqtt_server_.connect()->wait();
    subscribe(request_topic_);
}

void MQTTRPCServer::stop() {
    mqtt_server_.disconnect()->wait();
}

void MQTTRPCServer::subscribe(const std::string& topic) {
    mqtt_server_.subscribe(topic, 1)->wait();
}

void MQTTRPCServer::publish(const std::string& topic, const nlohmann::json& message) {
    std::cout << "Publishing message: " << message.dump() << ", topic:" << topic << std::endl;
    try {
        mqtt::message_ptr msg = mqtt::make_message(topic, message.dump());
        auto token = mqtt_server_.publish(msg);
        std::cout << "connected? :" << mqtt_server_.is_connected() << std::endl;   // 这句打印语句不可删
        //std::cout << "Waiting for publication of message to topic " << topic << std::endl;
        token->wait();
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error publishing message to topic " << topic << ": " << exc.what() << std::endl;
    } catch(...) {
        std::cerr << "Error publishing message to topic " << topic << std::endl;
    }
    std::cout << "Message published" << std::endl;

}

void MQTTRPCServer::register_method_handler(const std::string& method, 
                                            MQTTRequestHandle handler) {

    method_handlers_[method] = handler;                                            
}

void MQTTRPCServer::on_message(const mqtt::const_message_ptr& message) {
    auto jmsg = nlohmann::json::parse(message->to_string());
    std::string method = jmsg.value("method", "");
    std::string req_id = jmsg.value("req_id", "");
    std::string resp_topic = jmsg.value("resp_topic", "");
    bool need_reply = jmsg.value("need_reply", true);   // 默认需要回复

    std::cout << "on message:  Received request: " << jmsg.dump() << std::endl;
    if(!need_reply) {   // 不需要回复，直接丢弃
        std::cout << "No need to reply" << std::endl;
        return;
    }
     nlohmann::json response;
     if(method_handlers_.count(method)) {
        response = method_handlers_[method](jmsg);
     } else {
        response = nlohmann::json{{"result", "error"}, {"error_msg", "method not found"}};
     }

     response["req_id"] = req_id;
     this->publish(resp_topic, response);
}





