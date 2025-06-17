#include <iostream>
#include <httplib.h>
#include "gateway.h"

int main() {
    // 初始化网关
    Gateway gateway;

    // 启动HTTP服务器
    httplib::Server server;

    server.Post("/api", [&](const httplib::Request &req, httplib::Response &res) {
        // 处理请求
        std::string response = gateway.handleRequest(req.body);
        res.set_content(response, "application/json");
    });

    std::cout << "服务器正在运行，监听 8080 端口..." << std::endl;
    server.listen("0.0.0.0", 8080);

    return 0;
}