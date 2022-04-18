//
// Created by crazy on 12.04.2022.
//

#ifndef MYMINDUSTRY_EDITOR_H
#define MYMINDUSTRY_EDITOR_H


#include "../engine/engine.h"

class BottomPanel {
private:
    engine::EntitiesManager *m_pEntitiesManager;
    engine::AssetsManager *m_pAssetsManager;
    engine::ConfigManager *m_pConfigManager;
    engine::MemoryManager *m_pMemoryManager;
    engine::Grid m_grid;
    std::map<str, engine::ButtonPtr> m_mpButtons;

    engine::SmartStr *m_pSelectedBlockId;

public:

    void loadResources() {
        m_pEntitiesManager = engine::EntitiesManager::getInstance();
        m_pAssetsManager = engine::AssetsManager::getInstance();
        m_pConfigManager = engine::ConfigManager::getInstance();
        m_pMemoryManager = engine::MemoryManager::getInstance();

        m_pSelectedBlockId = m_pMemoryManager->getStringVariable("editor_selectedBlockId");


        json blocksConfig = m_pConfigManager->getJson("blocks");


        sf::Vector2f screenResolution = {m_pConfigManager->getJson("window")["width"],
                                         m_pConfigManager->getJson("window")["height"]};


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

        m_grid.setRows(1);
        m_grid.setCols(10);
        m_grid.setSize({64 * 10, 64});
        m_grid.setResizeButtons(true);
        m_grid.setPosition({0, screenResolution.y - 64});

        int column = 0;
        std::map<str, str> blocksIdsNames = blocksConfig["ids"];

        for (auto &blockInfo: blocksIdsNames) {

            engine::ButtonPtr button = std::make_shared<engine::Button>();
            m_grid.addEntity(button, column, 0);
            engine::ImagePtr image = m_pAssetsManager->getImage(blockInfo.second);
            image->setSize(60, 60);
            button->setImage(image);
            button->setStyle(buttonStyle);
            m_mpButtons[blockInfo.first] = button;
            m_pEntitiesManager->attach(button);

            column++;
        }

        m_grid.align("center");

    }

    void initialize() {


    }

    void draw(sf::RenderTarget &rt) {

    }

    void update() {

        for (auto &buttonInfo: m_mpButtons) {
            if (buttonInfo.second->isClicked()) {
                for (auto &buttonInfo2: m_mpButtons)
                    buttonInfo2.second->activate();
                m_pSelectedBlockId->setValue(buttonInfo.first);
                buttonInfo.second->deactivate();
            }
        }
    };


};

class Map {
private:
    engine::ConfigManager *m_pConfigManager;
    engine::AssetsManager *m_pAssetsManager;
    engine::CameraManager *m_pCameraManager;

    std::vector<std::vector<engine::SpritePtr>> m_vcSprites;

    int m_iBlockSize = 0;
    sf::Vector2i m_screenResolution;
public:
    void initialize() {
        m_pConfigManager = engine::ConfigManager::getInstance();
        m_pAssetsManager = engine::AssetsManager::getInstance();
        m_pCameraManager = engine::CameraManager::getInstance();

        m_iBlockSize = m_pConfigManager->getJson("blocks")["size"];
        json windowConfig = m_pConfigManager->getJson("window");
        m_screenResolution.x = windowConfig["width"];
        m_screenResolution.y = windowConfig["height"];

    }

    void update() {
        auto cameraPosition = m_pCameraManager->getCurrentTickShift();

        for (auto &line: m_vcSprites) {
            for (auto &sprite: line) {
                sprite->move({-cameraPosition.x, -cameraPosition.y});
            }
        }
    }

    void draw(sf::RenderTarget &rt) {
        int x = 0, y = 0;
        auto cameraPosition = m_pCameraManager->getInvertedCameraPosition();

        for (auto &line: m_vcSprites) {
            x = 0;

            if (cameraPosition.y + m_screenResolution.y < y) break;
            if (y < cameraPosition.y - m_iBlockSize) {
                y += m_iBlockSize;
                continue;
            }

            for (auto &sprite: line) {
                if (cameraPosition.x + m_screenResolution.x < x) break;

                if (x < cameraPosition.x - m_iBlockSize) {
                    x += m_iBlockSize;
                    continue;
                }

                rt.draw(*sprite);
                x += m_iBlockSize;
            }


            y += m_iBlockSize;
        }
    }

    void setSize(const sf::Vector2i &mapSize) {
        m_vcSprites.clear();

        json blocksConfig = m_pConfigManager->getJson("blocks");
        std::map<str, str> resourcesIdsNames = blocksConfig["ids"];

        for (int y = 0; y < mapSize.y; y++) {

            std::vector<engine::SpritePtr> newLine;
            for (int x = 0; x < mapSize.x; x++) {
                engine::SpritePtr sprite = m_pAssetsManager->getSprite(resourcesIdsNames["0"]);
                sprite->setPosition(x * m_iBlockSize + 30, y * m_iBlockSize + 30);
                sprite->setOrigin(30, 30);
                newLine.emplace_back(sprite);
            }
            m_vcSprites.push_back(newLine);
        }

    }

    void addBlock(const str &blockId, const sf::Vector2f &pos, int rotation) {
        json blocksConfig = m_pConfigManager->getJson("blocks");
        std::map<str, str> resourcesIdsNames = blocksConfig["ids"];

        sf::Vector2i coords = {(int) pos.x / m_iBlockSize, (int) pos.y / m_iBlockSize};

        m_vcSprites[coords.y][coords.x]->setTexture(*m_pAssetsManager->getTexture(resourcesIdsNames[blockId]));
        m_vcSprites[coords.y][coords.x]->setRotation(rotation);
    }

    void save() {

    }
};

class Pointer : public engine::Entity {
private:
    engine::SpritePtr m_pSprite;
    engine::AssetsManager *m_pAssetsManager;
    engine::MemoryManager *m_pMemoryManager;
    engine::CameraManager *m_pCameraManager;
    engine::ConfigManager *m_pConfigManager;
    sf::RenderWindow *m_pMainWindow{};
    int m_iBlockSize{};
    engine::SmartStr *m_pSelectedBlockId{};
    json m_jnBlocksConfig;
    Map m_map;
public:
    Pointer() {
        m_pAssetsManager = engine::AssetsManager::getInstance();
        m_pMemoryManager = engine::MemoryManager::getInstance();
        m_pCameraManager = engine::CameraManager::getInstance();
        m_pConfigManager = engine::ConfigManager::getInstance();


    }

    void initialize() override {
        m_pMainWindow = m_pMemoryManager->getMainWindow();
        m_pSprite = m_pAssetsManager->getSprite("player01");
        m_pSprite->setPosition(getPosition());

        m_jnBlocksConfig = m_pConfigManager->getJson("blocks");

        m_iBlockSize = m_jnBlocksConfig["size"];

        m_pSelectedBlockId = m_pMemoryManager->getStringVariable("editor_selectedBlockId");

        m_map.initialize();
        m_map.setSize({10, 10});
        m_pSprite->setOrigin(30, 30);
    }

    void draw(sf::RenderTarget &rt) override {
        rt.draw(*m_pSprite);
    }

    void setTexture(const engine::TexturePtr &texture) {
        m_pSprite->setTexture(*texture, true);
    }


    void update() override {

        sf::Vector2i mousePosition;
        sf::Vector2f newPosition;

        sf::Vector2f cameraPos = m_pCameraManager->getInvertedCameraPosition();

        mousePosition = sf::Mouse::getPosition(*m_pMainWindow);

        mousePosition.x -= (int) cameraPos.x % m_iBlockSize;
        mousePosition.y -= (int) cameraPos.y % m_iBlockSize;

        newPosition.x = mousePosition.x - mousePosition.x % m_iBlockSize + (int) cameraPos.x % m_iBlockSize + 30;
        newPosition.y = mousePosition.y - mousePosition.y % m_iBlockSize + (int) cameraPos.y % m_iBlockSize + 30;

        m_pSprite->setPosition(newPosition);
        setPosition(newPosition);

        if (mousePosition.y >= 1080 - 64) {
            hide();
        } else {
            show();
        }

        if (m_pSelectedBlockId->isChanged())
            if (!m_pSelectedBlockId->getValue().empty())
                setTexture(m_pAssetsManager->getTexture(m_jnBlocksConfig["ids"][m_pSelectedBlockId->getValue()]));

        m_map.update();
    }

    void handleSFMLEvent(sf::Event &event) override {
        if (event.type == sf::Event::MouseButtonPressed) {

            sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_pMainWindow);
            sf::Vector2f cameraPos = m_pCameraManager->getInvertedCameraPosition();
            if (mousePosition.y < 1080 - 64)
                m_map.addBlock(m_pSelectedBlockId->getValue(),
                               {getPosition().x - cameraPos.x,
                                getPosition().y - cameraPos.y}, m_pSprite->getRotation());

        } else if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta == -1) {

                m_pSprite->rotate(90);
            } else {
                m_pSprite->rotate(-90);
            }
        }
    }

    Map *getMap() {
        return &m_map;
    }


};


class MapEditorScene : public engine::Scene {
private:
    engine::AssetsManager *m_pAssetsManager{};
    engine::ConfigManager *m_pConfigManager{};
    engine::EntitiesManager *m_pEntitiesManager{};
    engine::CameraManager *m_pCameraManager{};
    engine::MemoryManager *m_pMemoryManager;
    std::shared_ptr<Pointer> m_pointer = std::make_shared<Pointer>();

    BottomPanel m_bottomPanel;
    sf::Vector2i m_screenResolution;

    engine::SmartStr *m_pSelectedBlockId = new engine::SmartStr;
    Map *m_pMap;
public:
    void onLoadResources() override {
        m_pAssetsManager = engine::AssetsManager::getInstance();
        m_pConfigManager = engine::ConfigManager::getInstance();
        m_pEntitiesManager = engine::EntitiesManager::getInstance();
        m_pCameraManager = engine::CameraManager::getInstance();
        m_pMemoryManager = engine::MemoryManager::getInstance();

        m_pAssetsManager->loadTexturesFromPack("../resources/sprites/sprite_packs/floors_pack.json");
        m_pAssetsManager->loadTexturesFromPack("../resources/sprites/sprite_packs/walls_pack.json");
        m_pAssetsManager->loadTexturesFromPack("../resources/sprites/sprite_packs/storages_pack.json");
        m_pAssetsManager->loadTexture("../resources/sprites/player/player01.png");
        m_pAssetsManager->loadTexture("../resources/sprites/walls/unknown.png");

        m_pMemoryManager->addVariable("editor_selectedBlockId", m_pSelectedBlockId);
        m_pConfigManager->loadJson("../resources/config/blocks.json", "blocks");

        m_bottomPanel.loadResources();


    }


    void onInitializeScene() override {
        m_bottomPanel.initialize();

        json windowConfig = m_pConfigManager->getJson("window");
        m_screenResolution.x = windowConfig["width"];
        m_screenResolution.y = windowConfig["height"];

        m_pEntitiesManager->attach(m_pointer);

        m_pCameraManager->setMaxPosition({(float) 20000 - m_screenResolution.x,
                                          (float) 20000 - m_screenResolution.y});
        m_pCameraManager->setMinPosition({0, 0});

        m_pMap = m_pointer->getMap();
    }

    void onDraw(sf::RenderTarget &rt) override {

        m_bottomPanel.draw(rt);
        m_pMap->draw(rt);
    }

    void onUpdate() override {
        m_bottomPanel.update();
    }
};


#endif //MYMINDUSTRY_EDITOR_H
