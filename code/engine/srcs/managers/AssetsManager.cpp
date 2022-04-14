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


    SpritePtr AssetsManager::getSprite(const str &textureName) {
        auto found = m_mpTextures.find(textureName);
        if (found == m_mpTextures.end()) {
            m_pLoggingManager->logError("Texture (" + textureName + ") not found");
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

    SpritePtr AssetsManager::getSprite(const str &textureName, const sf::IntRect &rectangle) {
        auto found = m_mpTextures.find(textureName);
        if (found == m_mpTextures.end()) {
            m_pLoggingManager->logError("Texture (" + textureName + ") not found");
        }

        SpritePtr sprite(new sf::Sprite(*found->second, rectangle));
        return sprite;
    }


    void AssetsManager::free() {
        m_mpTextures.clear();
    }

    json AssetsManager::loadJson(const str &filePath) {
        std::ifstream jsonFile;
        jsonFile.open(filePath);
        str buffer, line;
        while (std::getline(jsonFile, line)) {
            buffer += line;
        }

        if (buffer.empty()) {
            m_pLoggingManager->logError("Failed to read " + filePath);
        }
        jsonFile.close();
        m_pLoggingManager->logInfo(filePath + " was successfully loaded");
        return nlohmann::json::parse(buffer);
    }

    void AssetsManager::loadTexturesFromPack(const str &jsonPackDataFile) {
        json jsonPackData = loadJson(jsonPackDataFile);


        str path = jsonPackData["path"];
        std::vector<std::vector<str>> groups = jsonPackData["names"];
        int blockSize = jsonPackData["block_size"];

        int x = 0, y = 0;

        for (auto &names: groups) {
            x = 0;
            for (auto &name: names) {
                TexturePtr texture(new sf::Texture);
                texture->loadFromFile(path, {x, y, blockSize, blockSize});
                m_mpTextures[name] = texture;
                if (m_bLogInfo)
                    m_pLoggingManager->logInfo(path + "(" + name + ")" + " was successfully loaded");

                x += blockSize;
            }

            y += blockSize;
        }



//        TexturePtr texture(new sf::Texture);
//        texture->loadFromFile(path);
//
//        m_mpTextures[fs::path(path).stem().string()] = texture;
//        if (m_bLogInfo)
//            m_pLoggingManager->logInfo(path + " was successfully loaded");

    }


}