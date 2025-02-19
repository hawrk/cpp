/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 14:17:11
 * @Description: app 升级类管理
 * @FilePath: /hv_demo/ota_app_manager.hpp
 */
#pragma once

#include <iostream>
#include <vector>

class OTAAppManager {
    public:
        OTAAppManager() = default;

        ~OTAAppManager() = default;

        // test
        void start();

        void set_app_name(const std::string& app_name) {
            app_name_ = app_name;
        }

        std::string get_app_name() const {
            return app_name_;
        }

        // 系统空间检查
        bool check_sys_space();

        // 备份节点服务
        bool backup_app_files();

        bool stop_app_nodes();

        // 更新节点服务程序
        bool update_app_nodes();

        // 重启节点服务并验证
        bool restart_app_nodes();

        // 回滚节点服务程序
        void rollback_app_files();

    private:
        std::string app_name_;   // 应用名称

};