/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 10:13:20
 * @Description: 
 * @FilePath: /omni_server/internal/ota/ota_mng_upgrade.hpp
 */
#pragma once

#include "../omni_base.hpp"

class OTAManagerUpgrade :public OmniBase {
    public:
        OTAManagerUpgrade();
        bool process() override;

private:
   
};