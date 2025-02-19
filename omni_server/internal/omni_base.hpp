/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 10:30:00
 * @Description: 
 * @FilePath: /omni_server/internal/omni_base.hpp
 */
#pragma once

#include <string>
#include <iostream>
#include "ota/ota_app_manager.hpp"
#include <memory>

enum OmniTask: uint8_t {
    NONE = 0,
    TASK_OTA_QUERY,   // 查询
    TASK_OTA_UPGRADE,  // 升级
    TASK_OTA_ROLLBACK  // 回滚
};

class OmniBase {
    public:
        virtual ~OmniBase() = default;

        virtual bool process() = 0;

        std::tuple<int, std::string, std::string> get_http_resp() const { 
            return std::make_tuple(http_ret_code_, http_ret_msg_, http_ret_data_); 
        }

        void set_http_resp(int ret_code, const std::string& ret_msg, const std::string& ret_data) {
            http_ret_code_ = ret_code;
            http_ret_msg_ = ret_msg;
            http_ret_data_ = ret_data;
        }

        void set_body_str(const std::string& body) {  body_str_ = body; }
        

    protected:
        std::shared_ptr<OTAAppManager> app_manager_;    // 处理更新的应用管理器

        std::string body_str_;   // HTTP请求的body数据

        int http_ret_code_ = 0;   // HTTP返回码
        std::string http_ret_msg_;     // HTTP返回信息
        std::string http_ret_data_;    // HTTP返回数据

    private:

};