//
// Created by crazy on 02.04.2022.
//

#include "../../include/managers/ScenesManager.h"


namespace engine {
    ScenesManager *ScenesManager::s_pSelf = nullptr;


    bool ScenesManager::deleteInstance() {
        if (s_pSelf) {
            delete s_pSelf;
            s_pSelf = nullptr;
            return true;
        }
        return false;
    }

    ScenesManager *ScenesManager::getInstance() {

        if (!s_pSelf) {
            s_pSelf = new ScenesManager();
        }

        return s_pSelf;
    }

    ScenesManager::ScenesManager() {
        m_pLoggingManager = LoggingManager::getInstance();
        m_pLoggingManager->logInfo("ScenesManager initialized");
    }

    void ScenesManager::addScene(int id, const ScenePtr &scene) {
        m_mpScenes.emplace(id, scene);

        m_pLoggingManager->logInfo("Added new scene (id = " + std::to_string(id) + ")");

        if (m_pActiveScene == nullptr)
            setActiveScene(id);

    }

    void ScenesManager::updateScene() {
        m_pActiveScene->update();
    }

    void ScenesManager::drawScene(sf::RenderWindow &window) {
        m_pActiveScene->draw(window);
    }

    void ScenesManager::setActiveScene(int id) {
        if (m_mpScenes.find(id) == m_mpScenes.end()) {
            m_pLoggingManager->logError("Scene with id = " + std::to_string(id) + " has not be found");
            return;
        }

        if (m_pActiveScene != nullptr) {
            destroyActiveScene();

        }


        m_pActiveScene = m_mpScenes.at(id);


        m_pLoggingManager->logInfo("New active scene is set (id = " + std::to_string(id) + ")");
        m_pActiveScene->onLoadResources();
        m_pLoggingManager->logInfo("Resources loaded");
        m_pActiveScene->init();
        m_pLoggingManager->logInfo("Scene initialized");

    }

    void ScenesManager::handleSFMLEvent(sf::Event &event) {
        m_pActiveScene->handleSFMLEvent(event);
    }

    void ScenesManager::destroyActiveScene() {
        m_pActiveScene->destroy();
        m_pLoggingManager->logInfo("Scene destroyed");
    }

}