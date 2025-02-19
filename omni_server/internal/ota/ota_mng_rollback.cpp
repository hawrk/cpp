/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 11:55:40
 * @Description: 
 * @FilePath: /omni_server/internal/ota/ota_mng_rollback.cpp
 */

#include "ota_mng_rollback.hpp"

OTAManagerRollback::OTAManagerRollback() {
    app_manager_ = std::make_shared<OTAAppManager>();
}



bool OTAManagerRollback::process() {
    std::cout << "Rollback OTA" << std::endl;

    return true;

}