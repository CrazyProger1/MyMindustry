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
        m_pCameraManager = CameraManager::getInstance();


    }

    int EntitiesManager::attach(const EntityPtr &entity) {
        m_iCurrentEntityId++;
//        m_mpEntities.insert(std::pair<int, EntityPtr>(m_iCurrentEntityId, ent)); // entity
        m_mpEntities.emplace(m_iCurrentEntityId, entity);
        return m_iCurrentEntityId;
    }

    void EntitiesManager::drawEntities(sf::RenderTarget &rt) {
        for (auto e: m_mpEntities)
            if (!e.second->isHidden())
                e.second->draw(rt);
    }

    void EntitiesManager::updateEntities() {

        for (auto e: m_mpEntities) {
            if (m_pCameraManager->isCameraShiftingNow() && e.second->isDependsOnCamera()) {
                e.second->handleCameraShifting(m_pCameraManager->getCurrentTickShift());
            }
            e.second->update();
        }


    }

    void EntitiesManager::handleSFMLEvent(sf::Event &event) {
        for (auto e: m_mpEntities)
            e.second->handleSFMLEvent(event);

    }

    void EntitiesManager::initEntities() {
        for (auto e: m_mpEntities)
            e.second->init();

        m_pLoggingManager->logInfo("Entities initialized");
    }

    void EntitiesManager::clear() {
//        for (auto &m_mpEntity: m_mpEntities) {
//            delete (m_mpEntity.second);
//        }
        m_mpEntities.clear();
        m_iCurrentEntityId = 0;
    }
}