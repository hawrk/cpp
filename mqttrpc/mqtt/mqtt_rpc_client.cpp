
#include "mqtt_rpc_client.hpp"

#include <uuid/uuid.h>

MQTTRPCClient::MQTTRPCClient(const std::string& broker_url,
                     const std::string& client_id,
                     const std::string& request_topic,
                     const std::string& response_topic)
                  : broker_url_(broker_url),
                    client_id_(client_id),
                    request_topic_(request_topic),
                    response_topic_(response_topic),
                    mqtt_client_(broker_url, client_id) {

    mqtt_client_.set_message_callback([this](const mqtt::const_message_ptr& message) {
        this->on_message(message);
    });
}

MQTTRPCClient::~MQTTRPCClient() {
    this->stop();
}

void MQTTRPCClient::start() {
    mqtt_client_.connect()->wait();
    std::cout << "subscribe topic:" << response_topic_ << std::endl;
    subscribe(response_topic_);
    running_ = true;
    timeout_thread_ = std::thread([this]() {
        this->timeout_checker(); 
    });
}

void MQTTRPCClient::stop() {
    running_ = false;
    if(timeout_thread_.joinable()) {
        timeout_thread_.join();
    }
    try {
        mqtt_client_.disconnect()->wait();  
    } catch(const std::exception& e) {
        std::cout << "Error while disconnecting from MQTT broker: " << e.what() << std::endl;
    } catch(...) {
        std::cout << "Error while disconnecting from MQTT broker" << std::endl;
    }
}

void MQTTRPCClient::subscribe(const std::string& topic) {
    mqtt_client_.subscribe(topic, 1)->wait();
}

void MQTTRPCClient::publish(const std::string& topic, const nlohmann::json& payload) {
    mqtt::message_ptr msg = mqtt::make_message(topic, payload.dump());
    mqtt_client_.publish(msg)->wait();
}

std::string MQTTRPCClient::gen_uuid() {
    uuid_t uuid;
    char uuid_str[37];
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    return std::string(uuid_str);
}

void MQTTRPCClient::send_request(const std::string& method,
                                 const nlohmann::json& data,
                                 MQTTResponseCallback cb,
                                 int timeout_ms,
                                 bool need_reply) {

    std::string req_id = gen_uuid();  // 该ID需随机产生，并且保证唯一性，用来与响应消息进行匹配
    std::cout <<"Sending request: " << req_id << std::endl;
    nlohmann::json req = {
        {"method", method},
        {"data", data},
        {"req_id", req_id},
        {"resp_topic", response_topic_},
        {"need_reply", need_reply}
    };

    if(timeout_ms <= 0|| !need_reply) {   // 不需要回执或者不需要等待时间
        // fire-and-forget
        publish(request_topic_, req);
        return;
    }
    // 响应模式并且需要等待时间
    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pending_requests_[req_id] = PeddingRequest{cb, deadline, false};
    }
    publish(request_topic_, req);
}

void MQTTRPCClient::on_message(const mqtt::const_message_ptr& message) {
    std::cout << "on callback, received message: " << message->to_string() << std::endl;
    auto jmsg = nlohmann::json::parse(message->to_string());
    std::string req_id = jmsg.value("req_id", "");

    std::lock_guard<std::mutex> lock(mutex_);
    auto it = pending_requests_.find(req_id);   // 根据请求ID匹配响应
    if(it != pending_requests_.end() && !it->second.responded) {
        it->second.responded = true;
        if(it->second.cb) {
            it->second.cb(req_id, jmsg, false);
        }
        pending_requests_.erase(it);    // 移除已匹配的请求
    }
}

void MQTTRPCClient::timeout_checker() {
    while(running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto now = std::chrono::steady_clock::now();
        std::vector<std::string> to_remove;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            for(auto& [req_id, pending] : pending_requests_) {
                if(!pending.responded && pending.deadline < now) {
                    // 超时，调用回调函数
                    nlohmann::json timeout_resp ={
                        {"req_id", req_id},
                        {"timeout", true}
                    };
                    pending.responded = true;
                    if(pending.cb) {
                        pending.cb(req_id, timeout_resp, true);
                    }
                     to_remove.push_back(req_id);
                }
            }
            // 移除已超时的请求
            for(auto& req_id : to_remove) {
                pending_requests_.erase(req_id);
            }
        }
    }
}