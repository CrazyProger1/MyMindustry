//
// Created by crazy on 02.04.2022.
//

#include "../../include/managers/MemoryManager.h"


namespace engine {
    MemoryManager *MemoryManager::s_pSelf = nullptr;


    bool MemoryManager::deleteInstance() {
        if (s_pSelf) {
            delete s_pSelf;
            s_pSelf = nullptr;
            return true;
        }
        return false;
    }

    MemoryManager *MemoryManager::getInstance() {

        if (!s_pSelf) {
            s_pSelf = new MemoryManager();
        }

        return s_pSelf;
    }

    MemoryManager::MemoryManager() {
        m_pLoggingManager = LoggingManager::getInstance();
        m_pLoggingManager->logInfo("MemoryManager initialized");
    }

    void MemoryManager::setMainWindow(sf::RenderWindow *window) {
        m_pMainWindow = window;
    }

    sf::RenderWindow *MemoryManager::getMainWindow() {
        return m_pMainWindow;
    }
}