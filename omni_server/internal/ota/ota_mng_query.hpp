/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 10:13:49
 * @Description: 
 * @FilePath: /omni_server/internal/ota/ota_mng_query.hpp
 */
#pragma once

#include "../omni_base.hpp"

class OTAManagerQuery : public OmniBase {
    public:
        OTAManagerQuery();

        bool process() override;

private:
   
};