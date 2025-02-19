/*
 * @Author: hawrkchen
 * @Date: 2024-12-12 14:13:10
 * @Description: 
 * @FilePath: /hv_demo/handler/handler.hpp
 */
#pragma once

#include "hv/HttpService.h"
#include "../internal/omni_factory.hpp"

class Handler  {
    public:

        Handler() = default;


        static int preprocessor(HttpRequest* req, HttpResponse* res);
        static  int error_handler(const HttpContextPtr& ctx);

        // middleware
        static int auth_middleware(HttpRequest* req, HttpResponse* res);

        static int ota_post_handler(HttpRequest* req, HttpResponse* res);

    private:
        static  int response_status(const HttpContextPtr& ctx, int code = 200, const char* message =  nullptr);

        static  int response_status(const HttpResponseWriterPtr& writer, int code = 200, const char* message = nullptr);

        static  int response_status(HttpResponse* res, int code = 200, const char* message = nullptr);

};