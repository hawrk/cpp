/*
 * @Author: hawrkchen
 * @Date: 2024-12-12 13:55:47
 * @Description: 
 * @FilePath: /hv_demo/router.hpp
 */
#pragma once

#include "hv/HttpService.h"

class Router {
    public:
        static void RegisterRoutes(hv::HttpService& router);

    private:
};