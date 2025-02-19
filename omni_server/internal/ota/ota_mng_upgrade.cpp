/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 11:55:28
 * @Description: 
 * @FilePath: /omni_server/internal/ota/ota_mng_upgrade.cpp
 */

#include "ota_mng_upgrade.hpp"

OTAManagerUpgrade::OTAManagerUpgrade() {

    app_manager_ = std::make_shared<OTAAppManager>();
}

bool OTAManagerUpgrade::process() {
    std::cout << "Upgrade process" << std::endl;

    return true;
}


