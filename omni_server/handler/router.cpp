/*
 * @Author: hawrkchen
 * @Date: 2024-12-12 13:55:59
 * @Description: 
 * @FilePath: /hv_demo/handler/router.cpp
 */


#include "router.hpp"
#include "omni_handler.hpp"

void Router::RegisterRoutes(hv::HttpService& router) 
{
    router.preprocessor = Handler::preprocessor;

    router.Use(Handler::auth_middleware);

    router.POST("/ota", Handler::ota_post_handler);


}