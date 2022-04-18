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

    void MemoryManager::updateVariables() {
        for (auto &var: m_mpVariables) {
            static_cast<SmartVariable *>(var.second)->update();
        }
    }


    void *MemoryManager::getVariable(const str &name) {
        return m_mpVariables.at(name);
    }

    void MemoryManager::addVariable(const str &name, SmartVariable *variable) {
        m_mpVariables[name] = variable;
    }

    SmartStr *MemoryManager::getStringVariable(const str &name) {
        return static_cast<SmartStr *>(m_mpVariables.at(name));
    }

    void MemoryManager::clearVariables() {
        for (auto &var: m_mpVariables) {
            delete static_cast<SmartVariable *>(var.second);
        }
        m_mpVariables.clear();
    }

    void MemoryManager::pushSignal(int signal) {
        m_vcSignals.push_back(signal);
    }

    std::vector<int> &MemoryManager::getSignals() {
        return m_vcSignals;
    }

    void MemoryManager::clearSignals() {
        m_vcSignals.clear();
    }
}