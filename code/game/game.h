//
// Created by crazy on 01.04.2022.
//

#ifndef MYMINDUSTRY_GAME_H
#define MYMINDUSTRY_GAME_H

#include "scenes.h"

class Game : public engine::GameCore {
private:
public:
    void onUpdate() override {

    }

    void onDraw(sf::RenderTarget &rt) override {

    }

    void onTerminate() override {

    }

    void onSFMLEvent(sf::Event &event) override {
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Escape)
                terminate();


    }
};

#endif //MYMINDUSTRY_GAME_H
