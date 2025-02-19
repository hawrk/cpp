/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 15:36:48
 * @Description: 
 * @FilePath: /hv_demo/test/test_app_manager.cpp
 */

#include "../internal/ota/ota_app_manager.hpp"


int main() {
    OTAAppManager app_manager;

    app_manager.set_app_name("http_server");

    app_manager.check_sys_space();

    app_manager.stop_app_nodes();
}