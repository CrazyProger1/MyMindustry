//
// Created by crazy on 02.04.2022.
//

#ifndef MYMINDUSTRY_ENTITY_H
#define MYMINDUSTRY_ENTITY_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "./types.h"


namespace engine {
    class Entity {
    private:
        sf::Vector2f m_position;

        str m_sType = "entity";

        bool m_bDependsOnCamera = false;

        bool m_bIsHidden = false;

    public:


        Entity() = default;


        void setType(const str &type);

        virtual void setPosition(const sf::Vector2f &position);

        virtual void setPosition(float x, float y);

        void setCameraDependent(bool dependsOnCameraView = true);

        str &getType();

        sf::Vector2f &getPosition();


        [[nodiscard]] bool isDependsOnCamera() const;

        [[nodiscard]] bool isHidden() const;

        void hide();

        void show();

        void init();

        virtual void move(const sf::Vector2f &offset);

        virtual void move(float offsetX, float offsetY);


        virtual void initialize() {};

        virtual void draw(sf::RenderTarget &rt) {};

        virtual void update() {};

        virtual void handleSFMLEvent(sf::Event &event) {};

        virtual void handleCameraShifting(sf::Vector2f shift) {};

    };

    typedef std::shared_ptr<Entity> EntityPtr;
}


#endif //MYMINDUSTRY_ENTITY_H
