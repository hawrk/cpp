/*
 * @Author: hawrkchen
 * @Date: 2024-12-12 13:54:08
 * @Description: 
 * @FilePath: /omni_server/omni_server.cpp
 */
#include "hv/HttpServer.h"
#include "hv/hlog.h"
//#include "hv/hmain.h"

#include "handler/router.hpp"

#include <fstream>


hv::HttpServer g_http_server;
hv::HttpService g_http_service;
//main_ctx_t  g_main_ctx;


void signalHandler(int signum) {
    LOGI("get signal :%d, exit", signum);
    exit(signum);
}

int parse_confile(const char* confile) {
    std::ifstream ifs(confile);
    if(!ifs) {
        LOGE("open config file %s failed", confile);
        return -1;
    }
    nlohmann::json j;
    ifs >> j;
    // logfile
    if(std::string val = j["log"]["file"].get<std::string>(); !val.empty()) {
        //strncpy(g_main_ctx.logfile, str.c_str(), sizeof(g_main_ctx.logfile) - 1);
        hlog_set_file(val.c_str());
    }
    // loglevel
    if(std::string val = j["log"]["level"].get<std::string>(); !val.empty()) {
        hlog_set_level_by_str(val.c_str());
    }
    // port
    if(int port = j["server"]["port"].get<int>(); port > 0) {
        g_http_server.port = port;
    } else {
        g_http_server.port = 8090;
    }
    return 0;
}

int main(int argc, char* argv[]) 
{
    //main_ctx_init(argc, argv);
    parse_confile("../etc/config.json");
    // 添加信号
    signal(SIGINT, signalHandler);    // 处理 Ctrl-C
    signal(SIGQUIT, signalHandler);   // 处理 "Ctrl-\"

    
    Router::RegisterRoutes(g_http_service);
    g_http_server.registerHttpService(&g_http_service);

    g_http_server.run();
    
    return 0;
}