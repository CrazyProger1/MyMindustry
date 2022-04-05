//
// Created by crazy on 04.04.2022.
//

#include "../../include/GUI/Image.h"

namespace engine {

    Image::Image() {
        m_pLoggingManager = LoggingManager::getInstance();
    }

    Image::Image(const str &path) {
        m_sImagePath = path;
        m_pLoggingManager = LoggingManager::getInstance();
    }

    void Image::initialize() {
        setType("image");

        if (!m_texture.loadFromFile(m_sImagePath)) {
            m_pLoggingManager->logError("Unable to open file (" + m_sImagePath + ")");

        }
        m_sprite.setTexture(m_texture);
        m_sprite.setPosition(getPosition());

        sf::Vector2u originalSize = m_texture.getSize();
        sf::Vector2f scale = m_sprite.getScale();
        m_size.x = originalSize.x * scale.x;
        m_size.y = originalSize.y * scale.y;
    }

    void Image::setSize(const sf::Vector2f &size) {
        sf::Vector2u originalSize = m_texture.getSize();

        sf::Vector2f scale = {size.x / originalSize.x, size.y / originalSize.y};
        m_sprite.setScale(scale);
        initialize();
    }

    void Image::setSize(float w, float h) {
        sf::Vector2u originalSize = m_texture.getSize();

        sf::Vector2f scale = {w / originalSize.x, h / originalSize.y};
        m_sprite.setScale(scale);
        initialize();
    }

    void Image::setImageFilepath(const str &path) {
        m_sImagePath = path;
        initialize();
    }

    void Image::setScale(const sf::Vector2f &scale) {
        m_sprite.setScale(scale);
        initialize();
    }

    void Image::setScale(float factorX, float factorY) {
        m_sprite.setScale(factorX, factorY);
        initialize();
    }

    sf::Vector2f Image::getSize() {
        return m_size;
    }

    void Image::draw(sf::RenderTarget &rt) {
        rt.draw(m_sprite);
    }


}
