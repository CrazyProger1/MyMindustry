//
// Created by crazy on 05.04.2022.
//

#ifndef MYMINDUSTRY_SCENES_H
#define MYMINDUSTRY_SCENES_H

#include "../engine/engine.h"


class Menu : public engine::Scene {
private:
    engine::Button m_button1;
public:
    void onUpdate() override {
        if (m_button1.isClicked())
            engine::ScenesManager::getInstance()->setActiveScene(2);
    }

    void onLoadResources() override {

    }

    void onInitializeScene() override {
        engine::ButtonStyle buttonStyle(
                {100, 100},
                {250, 250, 0},
                {240, 0, 0}
        );

        m_button1.setStyle(buttonStyle);
        attachEntity(&m_button1);
    }

    void onSFMLEvent(sf::Event &event) override {
        if (event.type == sf::Event::KeyPressed) {
            engine::ScenesManager::getInstance()->setActiveScene(2);
        }
    }
};

class SideBar {
private:
    sf::Vector2f m_position;
    sf::RectangleShape m_sidebarRect;

    engine::EntitiesManager *m_pEntitiesManager;

    engine::Button btnConvs;
    engine::Button btnDrills;
    engine::Button btnManufactures;
    engine::Button btnPipes;
    engine::Button btnWeapons;
    engine::Button btnElectronics;
    engine::Button btnDefenses;
    engine::Button btnOther;

    engine::Image imgConvs;
    engine::Image imgDrills;
    engine::Image imgManufactures;
    engine::Image imgPipes;
    engine::Image imgWeapons;
    engine::Image imgElectronics;
    engine::Image imgDefenses;
    engine::Image imgOther;

public:
    SideBar() {
        m_pEntitiesManager = engine::EntitiesManager::getInstance();
    };

    SideBar(float x, float y) {
        m_pEntitiesManager = engine::EntitiesManager::getInstance();
        m_position.x = x;
        m_position.y = y;
    }

    explicit SideBar(sf::Vector2f position) {
        m_pEntitiesManager = engine::EntitiesManager::getInstance();
        m_position = position;
    }

    void setPosition(float x, float y) {
        m_position.x = x;
        m_position.y = y;
        initialize();
    }

    void setPosition(sf::Vector2f position) {
        m_position = position;
        initialize();
    }

    void initialize() {
        m_sidebarRect.setFillColor({100, 100, 100, 100});
        m_sidebarRect.setSize({4 * 64, 6 * 64});
        m_sidebarRect.setPosition(m_position);

        engine::ButtonStyle buttonStyle(
                {64, 64},
                {0, 0, 0, 0},
                {100, 100, 100, 100},
                {0, 0},
                {0, 0},
                0,
                {0, 0, 0},
                false,
                true,
                0,
                false,
                {135, 0, 0}
        );

        imgConvs.setImageFilepath("../resources/imgs/super/conveyors.png");
        imgDrills.setImageFilepath("../resources/imgs/super/drills.png");
        imgManufactures.setImageFilepath("../resources/imgs/super/manufacture.png");
        imgPipes.setImageFilepath("../resources/imgs/super/pipes.png");
        imgWeapons.setImageFilepath("../resources/imgs/super/weapons.png");
        imgElectronics.setImageFilepath("../resources/imgs/super/electronics.png");
        imgDefenses.setImageFilepath("../resources/imgs/super/defense.png");
        imgOther.setImageFilepath("../resources/imgs/super/other.png");


        btnConvs.setImage(imgConvs);
        btnDrills.setImage(imgDrills);
        btnManufactures.setImage(imgManufactures);
        btnPipes.setImage(imgPipes);
        btnWeapons.setImage(imgWeapons);
        btnElectronics.setImage(imgElectronics);
        btnDefenses.setImage(imgDefenses);
        btnOther.setImage(imgOther);

        btnConvs.setPosition(m_position.x, m_position.y);
        btnDrills.setPosition(m_position.x + 64, m_position.y);
        btnManufactures.setPosition(m_position.x + 128, m_position.y);
        btnPipes.setPosition(m_position.x + 64 * 3, m_position.y);
        btnWeapons.setPosition(m_position.x, m_position.y + 64);

        btnConvs.setStyle(buttonStyle);
        btnDrills.setStyle(buttonStyle);
        btnManufactures.setStyle(buttonStyle);
        btnPipes.setStyle(buttonStyle);
        btnWeapons.setStyle(buttonStyle);

        m_pEntitiesManager->attach(&btnConvs);
        m_pEntitiesManager->attach(&btnDrills);
        m_pEntitiesManager->attach(&btnManufactures);
        m_pEntitiesManager->attach(&btnPipes);
        m_pEntitiesManager->attach(&btnWeapons);
    }

    void update() {
        if (btnConvs.isClicked()) {
            btnConvs.deactivate();
            btnDrills.activate();
            btnManufactures.activate();
            btnPipes.activate();
            btnWeapons.activate();

        } else if (btnDrills.isClicked()) {
            btnDrills.deactivate();
            btnConvs.activate();
            btnManufactures.activate();
            btnPipes.activate();
            btnWeapons.activate();

        } else if (btnManufactures.isClicked()) {
            btnManufactures.deactivate();
            btnConvs.activate();
            btnDrills.activate();
            btnPipes.activate();
            btnWeapons.activate();

        } else if (btnPipes.isClicked()) {
            btnManufactures.activate();
            btnConvs.activate();
            btnDrills.activate();
            btnPipes.deactivate();
            btnWeapons.activate();

        } else if (btnWeapons.isClicked()) {
            btnWeapons.deactivate();
            btnManufactures.activate();
            btnConvs.activate();
            btnDrills.activate();
            btnPipes.activate();
        }
    }

    void draw(sf::RenderTarget &rt) {
        rt.draw(m_sidebarRect);
    }
};

class Main : public engine::Scene {
private:
    SideBar m_sideBar;
public:
    void onInitializeScene() override {
        m_sideBar.initialize();
        m_sideBar.setPosition(1920 - 4 * 64, 1080 - 6 * 64);
    }

    void onDraw(sf::RenderTarget &rt) override {
        m_sideBar.draw(rt);
    }

    void onUpdate() override {
        m_sideBar.update();
    }
};

#endif //MYMINDUSTRY_SCENES_H
