//
// Created by crazy on 05.04.2022.
//

#ifndef MYMINDUSTRY_ASSETSMANAGER_H
#define MYMINDUSTRY_ASSETSMANAGER_H

#include <SFML/Graphics.hpp>
#include <experimental/filesystem>
#include "../types.h"
#include "LoggingManager.h"
#include "../../nlohmann/json.hpp"
#include "../GUI/Image.h"

namespace fs = std::experimental::filesystem;

namespace engine {
    typedef std::shared_ptr<sf::Texture> TexturePtr;
    typedef std::shared_ptr<sf::Sprite> SpritePtr;

    class AssetsManager {
    private:
        LoggingManager *m_pLoggingManager;

        bool m_bLogInfo = true;

        std::map<str, std::shared_ptr<sf::Texture>> m_mpTextures;

        json loadJson(const str &filePath);

    protected:
        static AssetsManager *s_pSelf;

        AssetsManager();

        virtual ~AssetsManager() = default;

    public:
        static AssetsManager *getInstance();

        static bool deleteInstance();

        void loadTexturesFromDir(const str &dirPath);

        void loadTexture(const str &filePath);

        void loadTexturesFromPack(const str &jsonPackData);

        void free();

        TexturePtr getTexture(const str &name);

        SpritePtr getSprite(const str &textureName);

        SpritePtr getSprite(const str &textureName, const sf::IntRect &rectangle);

        ImagePtr getImage(const str &name);
    };
}


#endif //MYMINDUSTRY_ASSETSMANAGER_H
