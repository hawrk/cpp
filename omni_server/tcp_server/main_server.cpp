/*
 * @Author: hawrkchen
 * @Date: 2024-12-18 13:54:30
 * @Description: 
 * @FilePath: /omni_server/tcp_server/main_server.cpp
 */

#include "tcp_server.hpp"
#include <memory>

int main(int argc, char* argv[])    
{
    auto server = std::make_shared<OmniTCPServer>(8080, "127.0.0.1");

    server->start_serer();


    return 0;
}