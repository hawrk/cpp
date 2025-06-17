#include "gateway.h"
#include <iostream>
#include <string>
#include <json/json.h> // 假设使用一个JSON库

Gateway::Gateway() {
    // 构造函数
}

void Gateway::handleRequest(const std::string& request) {
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::string errs;

    // 解析JSON请求
    std::istringstream s(request);
    if (!Json::parseFromStream(readerBuilder, s, &jsonData, &errs)) {
        std::cerr << "JSON解析错误: " << errs << std::endl;
        return;
    }

    // 处理请求并生成响应
    Json::Value responseData;
    responseData["status"] = "success";
    responseData["message"] = "请求已成功处理";

    // 将响应转换为JSON字符串
    Json::StreamWriterBuilder writerBuilder;
    std::string response = Json::writeString(writerBuilder, responseData);

    // 返回响应（这里可以根据实际情况进行处理，例如发送回客户端）
    std::cout << "响应: " << response << std::endl;
}