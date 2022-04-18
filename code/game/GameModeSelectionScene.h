//
// Created by crazy on 15.04.2022.
//

#ifndef MYMINDUSTRY_GAMEMODESELECTIONSCENE_H
#define MYMINDUSTRY_GAMEMODESELECTIONSCENE_H

#include "../engine/engine.h"

class GameModeSelectionScene : public engine::Scene {
private:
public:
    void onLoadResources() override {
    }

    void onInitializeScene() override {
//        engine::ImprovedUsualButtonPtr improvedUsualButton = std::make_shared<engine::ImprovedUsualButton>();
//
//        engine::ButtonStyle buttonStyle(
//                {250, 50},
//                {0, 0, 0},
//                {0, 255, 0},
//                {0, 0},
//                {0, 0},
//                1,
//                {0, 255, 0},
//                true,
//                false,
//                10, // 10
//                false
//        );
//
//        improvedUsualButton->setPosition(100 , 100);
//
//        improvedUsualButton->setStyle(buttonStyle);
//        attachEntity(improvedUsualButton);
    }

    void onDraw(sf::RenderTarget &rt) override {

    }
};


#endif //MYMINDUSTRY_GAMEMODESELECTIONSCENE_H
