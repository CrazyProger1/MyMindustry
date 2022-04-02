//
// Created by crazy on 02.04.2022.
//

#include "../../include/managers/EntitiesManager.h"


namespace engine {
    EntitiesManager *EntitiesManager::s_pSelf = nullptr;


    bool EntitiesManager::deleteInstance() {
        if (s_pSelf) {
            delete s_pSelf;
            s_pSelf = nullptr;
            return true;
        }
        return false;
    }

    EntitiesManager *EntitiesManager::getInstance() {

        if (!s_pSelf) {
            s_pSelf = new EntitiesManager();
        }

        return s_pSelf;
    }

    EntitiesManager::EntitiesManager() {
        m_pLoggingManager = LoggingManager::getInstance();
        m_pLoggingManager->logInfo("EntitiesManager initialized");
    }
}