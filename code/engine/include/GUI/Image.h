//
// Created by crazy on 04.04.2022.
//

#ifndef MYMINDUSTRY_IMAGE_H
#define MYMINDUSTRY_IMAGE_H

#include <memory>
#include "../Entity.h"
#include "../managers/LoggingManager.h"


namespace engine {

    class Image : public Entity {
    private:
        str m_sImagePath;
        sf::Vector2f m_size;

        sf::Texture m_texture;
        sf::Sprite m_sprite;

        bool m_bTextureIsSet = false;

        LoggingManager *m_pLoggingManager;

    public:
        Image();

        explicit Image(const str &path);

        explicit Image(const sf::Texture &texture);


        void initialize() override;


        void setSize(const sf::Vector2f &size);

        void setSize(float w, float h);

        void setScale(const sf::Vector2f &scale);

        void setScale(float factorX, float factorY);

        void setImageFilepath(const str &path);

        void setTexture(const sf::Texture &texture);

        sf::Vector2f getSize();


        void draw(sf::RenderTarget &rt) override;


    };

    typedef std::shared_ptr<Image> ImagePtr;
}


#endif //MYMINDUSTRY_IMAGE_H
