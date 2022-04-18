//
// Created by crazy on 15.04.2022.
//

#include "MainMenuScene.h"

void MainMenuScene::onLoadResources() {
    m_pAssetsManager = engine::AssetsManager::getInstance();
    m_pConfigManager = engine::ConfigManager::getInstance();
    m_pScenesManager = engine::ScenesManager::getInstance();
    m_pMemoryManager = engine::MemoryManager::getInstance();

    json langPacksInfo = m_pConfigManager->loadJson("../resources/config/langs.json", "langs");
    m_jnMenuInfo = m_pConfigManager->loadJson("../resources/config/menu.json", "menu");
    m_pAssetsManager->loadTexture("../resources/imgs/backgrounds/background2.jpg");

    m_backgroundImage = m_pAssetsManager->getImage("background2");

    str selectedLang = langPacksInfo["selected"];
    str path = langPacksInfo[selectedLang]["path"];
    m_pConfigManager->loadLanguagePack(path, selectedLang);
}

void MainMenuScene::onInitializeScene() {
    engine::Grid grid;
    sf::Vector2f menuSize;
    menuSize.x = m_jnMenuInfo["menu_size"][0];
    menuSize.y = m_jnMenuInfo["menu_size"][1];
    grid.setSize(menuSize);

    engine::ButtonStyle buttonStyle(
            {250, 50},
            {0, 0, 0, 100},
            {0, 255, 0, 125},
            {0, 0},
            {0, 0},
            1,
            {0, 255, 0},
            true,
            false,
            10,
            false
    );

    engine::TextStyle textStyle(
            "../resources/fonts/consola.ttf",
            0,
            25,
            5,
            0,
            {0, 255, 0},
            {0, 0, 0},
            {0, 0, 0}
    );
    grid.setCols(1);
    grid.setPosition({1920 - menuSize.x,
                      1080 - menuSize.y});

    attachEntity(m_backgroundImage);

    int buttonCounter = 0;
    for (auto &buttonName: m_jnMenuInfo["buttons"]) {
        engine::ButtonPtr button = std::make_shared<engine::UsualButton>();
        engine::TextPtr text = std::make_shared<engine::Text>();

        button->setStyle(buttonStyle);
        text->setStyle(textStyle);

        text->setText(m_pConfigManager->getTranslation("MainMenu", buttonName));

        button->setText(text);

        grid.addEntity(button, 0, buttonCounter);
        m_mpButtons[buttonName] = button;
        attachEntity(button);
        buttonCounter++;
    }
    grid.setResizeButtons(false);
    grid.setRows(buttonCounter);

    grid.align("tl");


}

void MainMenuScene::onUpdate() {
    for (auto &nameButtonPair: m_mpButtons)
        if (nameButtonPair.second->isClicked()) {
            if (nameButtonPair.first == "NewGame")
                m_pScenesManager->setActiveScene(2);

            if (nameButtonPair.first == "Exit")
                m_pMemoryManager->pushSignal(engine::signals::EXIT);

//
        }

}
