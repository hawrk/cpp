/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 11:25:56
 * @Description: 
 * @FilePath: /omni_server/internal/ota/ota_mng_query.cpp
 */

#include "ota_mng_query.hpp"

OTAManagerQuery::OTAManagerQuery() {
    app_manager_ = std::make_shared<OTAAppManager>();
}


bool OTAManagerQuery::process() {
    std::cout << "Querying for OTA query..." << std::endl;

    std::cout << "fork some else func here" << std::endl;

    app_manager_->start();

    
    // 回包
    std::string data = "我知道你一定会来点赞的";

    set_http_resp(200, "我完成了任务，快来点赞",data);


    return true;
}

