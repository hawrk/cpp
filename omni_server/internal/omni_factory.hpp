/*
 * @Author: hawrkchen
 * @Date: 2024-12-09 10:09:18
 * @Description: 
 * @FilePath: /omni_server/internal/omni_factory.hpp
 */
#pragma once

#include <memory>
#include "omni_base.hpp"

#include "ota/ota_mng_query.hpp"
#include "ota/ota_mng_upgrade.hpp"
#include "ota/ota_mng_rollback.hpp"


class OmniFactory {
    public:
        static std::unique_ptr<OmniBase> createOmniManager(const OmniTask& type) {
            if (type == OmniTask::TASK_OTA_QUERY) {
                return std::make_unique<OTAManagerQuery>();
            } else if(type == OmniTask::TASK_OTA_UPGRADE) {
                return std::make_unique<OTAManagerUpgrade>();
            } else if(type == OmniTask::TASK_OTA_ROLLBACK) {
                return std::make_unique<OTAManagerRollback>();  
            } else {
                return nullptr;
            }
        }
};