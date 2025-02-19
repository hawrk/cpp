/*
 * @Author: hawrkchen
 * @Date: 2024-12-02 14:14:17
 * @Description: 
 * @FilePath: /hv_demo/http_server.cpp
 */


#include "hv/HttpServer.h"
#include "hv/hlog.h"
#include "nlohmann/json.hpp"
#include "hv/hasync.h"

using namespace hv;

using json = nlohmann::json;

static int response_status(HttpResponse* res, int code = 200, const char* message = nullptr) {
    if(message == nullptr) {
        message = http_status_str((enum http_status)code);
    }
    res->Set("code", code);
    res->Set("message", message);
    return code;
}

static int response_status(const HttpContextPtr& ctx, int code = 200, const char* message = nullptr) {
    response_status(ctx->response.get(), code, message);
    ctx->send();
    return code;
}

void initLog() {
    hlog_set_level(LOG_LEVEL_DEBUG);
    hlog_set_file("http_server.log");
    
}

void signalHandler(int signum) {
    LOGI("get signal :%d, exit", signum);
    exit(signum);
    
}

void signalHandlerInit() {
    // 添加信号
    signal(SIGINT, signalHandler);    // 处理 Ctrl-C
    signal(SIGQUIT, signalHandler);   // 处理 "Ctrl-\"
}

int main() 
{
    // 初始化日志
    initLog();
    // 处理信号
    signalHandlerInit();
    
    HttpService router;



    // get
    router.GET("/hello", [](HttpRequest* req, HttpResponse* res) {
        auto ret = res->String("Hello, World!");
        return ret;
    });

    // get data
    router.GET("/data", [](HttpRequest* req, HttpResponse* res) {
        static char data[] = "Hello, World0123456789!";
        return res->Data(data, sizeof(data) - 1);
    });

    // get json
    router.GET("/json", [](HttpRequest* req, HttpResponse* res) {
        res->json["name"] = "hawrkchen";
        res->json["age"] = 25;
        res->json["gender"] = "male";
        res->json["origin"] = req->client_addr.ip;
        res->json["url"] = req->url;
        res->json["args"] = req->query_params;
        res->json["headers"] = req->headers;
        
        return 200;
    });

    // post json
    router.POST("/echo", [](const HttpContextPtr& ctx) {

        hv::async([ctx]() {
            // 异步处理
            if(!ctx->is(APPLICATION_JSON)) {
                return response_status(ctx, HTTP_STATUS_BAD_REQUEST);
            }
            //return ctx->send(ctx->body(), ctx->type());
            //auto req_json = ctx->json();
            //std::string str = req_json.dump();
            //LOGD("%s",str.c_str());
            // get request body
            //std::string name = req_json["username"];
            //LOGD("get username:%s", name.c_str());

            json j;
            j["name"] = "hawrkchen";
            j["age"] = 25;
            j["gender"] = "male";
            j["origin"] = "127.0.0.1";
            j["url"] = "/json";
            j["args"] = "name=hawrkchen&age=25&gender=male"; 
            // 转化为string
            std::string str = j.dump();
            LOGD("ret %s",str.c_str());
            
            //printf("get request:%s ", ctx->request->query_params["username"].c_str());
            return ctx->send(ctx->body(), ctx->type());
        });
        
        return 0;
   
    });

    hlogd("get http server running on port 8080");

    http_server_t server;

    server.port = 8080;
    server.service = &router;

    server.worker_threads = 4;

    http_server_run(&server, 1);

    return 0;

}
