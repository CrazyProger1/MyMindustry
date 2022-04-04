//
// Created by crazy on 02.04.2022.
//

#include "../include/Entity.h"

namespace engine {

    void Entity::setType(const str &type) {
        m_sType = type;
    }

    str &Entity::getType() {
        return m_sType;
    }

    void Entity::init() {
        initialize();
    }

    void Entity::setPosition(const sf::Vector2f &position) {
        m_position = position;
    }

    void Entity::setPosition(float x, float y) {
        m_position.x = x;
        m_position.y = y;
    }

    void Entity::move(const sf::Vector2f &offset) {
        m_position.x += offset.x;
        m_position.y += offset.y;
    }

    void Entity::move(float offsetX, float offsetY) {
        m_position.x += offsetX;
        m_position.y += offsetY;
    }

}