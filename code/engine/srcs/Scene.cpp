//
// Created by crazy on 02.04.2022.
//

#include "../include/Scene.h"


namespace engine {


    void Scene::update() {
        onUpdate();
    }

    void Scene::draw(sf::RenderTarget &rt) {
        onDraw(rt);
    }

    Scene::Scene() {
        m_pEntitiesManager = EntitiesManager::getInstance();
    }

}