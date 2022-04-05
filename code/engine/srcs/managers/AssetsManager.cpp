//
// Created by crazy on 05.04.2022.
//

#include "../../include/managers/AssetsManager.h"

namespace engine {
    AssetsManager *AssetsManager::s_pSelf = nullptr;

    AssetsManager::AssetsManager() {
        m_pLoggingManager = LoggingManager::getInstance();
        m_pLoggingManager->logInfo("AssetsManager initialized");
    }


    AssetsManager *AssetsManager::getInstance() {
        if (!s_pSelf) {
            s_pSelf = new AssetsManager();
        }

        return s_pSelf;
    }

    bool AssetsManager::deleteInstance() {
        if (s_pSelf) {
            delete s_pSelf;
            s_pSelf = nullptr;
            return true;
        }
        return false;
    }
}