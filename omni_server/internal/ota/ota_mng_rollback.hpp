/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 10:13:49
 * @Description: 
 * @FilePath: /omni_server/internal/ota/ota_mng_rollback.hpp
 */
#pragma once

#include "../omni_base.hpp"


class OTAManagerRollback :public OmniBase {
    public:
        OTAManagerRollback();
        bool process() override;

private:
   
};