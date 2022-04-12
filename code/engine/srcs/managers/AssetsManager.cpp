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



    void AssetsManager::loadTexturesFromDir(const str &dirPath) {
        for (const auto &f: fs::directory_iterator(dirPath)) {
            TexturePtr texture(new sf::Texture);
            texture->loadFromFile(f.path().string());
            m_mpTextures[f.path().stem().string()] = texture;
            if (m_bLogInfo)
                m_pLoggingManager->logInfo(f.path().string() + " was successfully loaded");
        }
    }

    void AssetsManager::loadTexture(const str &filePath) {
        TexturePtr texture(new sf::Texture);
        texture->loadFromFile(filePath);
        m_mpTextures[fs::path(filePath).stem().string()] = texture;
        if (m_bLogInfo)
            m_pLoggingManager->logInfo(filePath + " was successfully loaded");
    }

    TexturePtr AssetsManager::getTexture(const str &name) {
        auto found = m_mpTextures.find(name);
        if (found == m_mpTextures.end()) {
            m_pLoggingManager->logError("Texture (" + name + ") not found");
        }
        return found->second;
    }


    SpritePtr AssetsManager::getSprite(const str &name) {
        auto found = m_mpTextures.find(name);
        if (found == m_mpTextures.end()) {
            m_pLoggingManager->logError("Texture (" + name + ") not found");
        }

        SpritePtr sprite(new sf::Sprite(*found->second));
        return sprite;
    }

    ImagePtr AssetsManager::getImage(const str &name) {
        auto found = m_mpTextures.find(name);
        if (found == m_mpTextures.end()) {
            m_pLoggingManager->logError("Texture (" + name + ") not found");
        }
        ImagePtr image(new Image(*found->second));
        return image;
    }


    void AssetsManager::free() {
        m_mpTextures.clear();
    }


}