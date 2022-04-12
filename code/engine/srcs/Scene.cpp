//
// Created by crazy on 02.04.2022.
//

#include "../include/Scene.h"


namespace engine {


    void Scene::update() {
        m_pCameraManager->update();
        onUpdate();
        m_pEntitiesManager->updateEntities();

    }

    void Scene::draw(sf::RenderTarget &rt) {
        onDraw(rt);
        m_pEntitiesManager->drawEntities(rt);
    }

    Scene::Scene() {
        m_pEntitiesManager = EntitiesManager::getInstance();
        m_pLoggingManager = LoggingManager::getInstance();
        m_pAssetsManager = AssetsManager::getInstance();
        m_pCameraManager = CameraManager::getInstance();
    }

    void Scene::handleSFMLEvent(sf::Event &event) {
        m_pCameraManager->handleSFMLEvent(event);
        m_pEntitiesManager->handleSFMLEvent(event);
        onSFMLEvent(event);
    }

    void Scene::init() {
        onInitializeScene();
        m_pEntitiesManager->initEntities();
    }

    int Scene::attachEntity(const EntityPtr &entity) {
        return m_pEntitiesManager->attach(entity);
    }

    void Scene::destroy() {
        m_pEntitiesManager->clear();
        m_pAssetsManager->free();
        onDestroy();
    }


}