//
// Created by crazy on 02.04.2022.
//

#ifndef MYMINDUSTRY_ENTITY_H
#define MYMINDUSTRY_ENTITY_H

#include <SFML/Graphics.hpp>
#include "./types.h"


namespace engine {
    class Entity {
    private:
        sf::Vector2f m_position;

        str m_sType = "entity";


    public:


        Entity() = default;


        void setType(const str &type);

        void setPosition(const sf::Vector2f &position);

        void setPosition(float x, float y);

        str &getType();

        sf::Vector2f &getPosition();


        void init();

        void move(const sf::Vector2f &offset);

        void move(float offsetX, float offsetY);


        virtual void initialize() {};

        virtual void draw(sf::RenderTarget &rt) {};

        virtual void update() {};

        virtual void handleSFMLEvent(sf::Event &event) {};


    };
}


#endif //MYMINDUSTRY_ENTITY_H
