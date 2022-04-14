//
// Created by crazy on 05.04.2022.
//

#ifndef MYMINDUSTRY_SCENES_H
#define MYMINDUSTRY_SCENES_H

#include <regex>
#include "../engine/engine.h"
#include <stdlib.h>
#include <time.h>

std::vector<std::string> splitString(const std::string &str, char delim = '\n') {
    std::vector<std::string> tokens;

    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        tokens.push_back(token);
    }

    return tokens;
}

class Menu : public engine::Scene {
private:
    engine::ButtonPtr m_pButton{};
    engine::SpritePtr m_pSprite{};
    engine::TextPtr m_pText{};

public:
    void onLoadResources() override {
        m_pText = std::make_shared<engine::Text>();
        m_pButton = std::make_shared<engine::Button>();


    }

    void onInitializeScene() override {
        m_pButton->setSize(128, 64);
        m_pButton->setCenteringText(true);
        m_pButton->setCenteringImage(true);
        m_pText->setText("Hello World");
        m_pButton->setText(m_pText);

        attachEntity(m_pButton);
    }

    void onUpdate() override {

        if (m_pButton->isClicked()) {
            engine::ScenesManager *pScenesManager = engine::ScenesManager::getInstance();
            pScenesManager->setActiveScene(2);
        }
    }

};


class SideBar : public engine::Entity {
private:
    sf::RectangleShape m_sidebarRect;

    engine::EntitiesManager *m_pEntitiesManager;
    engine::AssetsManager *m_pAssetsManager;

    std::map<str, engine::ButtonPtr> buttons;

    std::vector<str> btnNames = {"conveyors",
                                 "drills",
                                 "electronics",
                                 "manufactures",
                                 "pipes",
                                 "weapons",
                                 "defenses",
                                 "others"};

public:
    SideBar() {
        m_pEntitiesManager = engine::EntitiesManager::getInstance();
        m_pAssetsManager = engine::AssetsManager::getInstance();
        setCameraDependent(false);
    };


    void initialize() override {
        auto selfPosition = getPosition();

        m_sidebarRect.setFillColor({100, 100, 100, 100});
        m_sidebarRect.setSize({4 * 64, 6 * 64});
        m_sidebarRect.setPosition(selfPosition);

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

        float xOffset;
        float yOffset = 0;


//        m_pAssetsManager->loadTexturesFromDir("../resources/sprites/sidebar");

        for (const auto &btnName: btnNames) {

            buttons[btnName] = std::make_shared<engine::Button>();
            buttons[btnName]->setStyle(buttonStyle);
            buttons[btnName]->setPosition(selfPosition.x + xOffset, selfPosition.y + yOffset);
            buttons[btnName]->setImage(m_pAssetsManager->getImage(btnName));

            xOffset += 64;
            if (xOffset == 256) {
                xOffset = 0;
                yOffset += 64;
            }

            m_pEntitiesManager->attach(buttons[btnName]);

        }


    }

    void update() override {
        for (const auto &btnName: btnNames) {
            if (buttons[btnName]->isClicked()) {
                buttons[btnName]->deactivate();
                for (const auto &btnName2: btnNames) {
                    if (btnName != btnName2) {
                        buttons[btnName2]->activate();
                    }

                }
            }
        }
    }

    void draw(sf::RenderTarget &rt) override {
        rt.draw(m_sidebarRect);
    }
};

class Storage : public engine::Entity {
private:

    engine::AssetsManager *m_pAssetsManager;
    engine::SpritePtr m_pSprite;

public:
    Storage() {
        m_pAssetsManager = engine::AssetsManager::getInstance();
        setCameraDependent(true);
    }

    void initialize() override {
        m_pSprite = m_pAssetsManager->getSprite("storage01");
        m_pSprite->setPosition(getPosition());
    }

    void draw(sf::RenderTarget &rt) override {
        rt.draw(*m_pSprite);
    }

    void handleCameraShifting(sf::Vector2f shift) override {
        m_pSprite->move(-shift.x, -shift.y);
    }
};

class Player : public engine::Entity {
private:
    engine::SpritePtr m_pSprite;
    engine::AssetsManager *m_pAssetsManager;
    engine::MemoryManager *m_pMemoryManager;
    engine::CameraManager *m_pCameraManager;
    engine::ConfigManager *m_pConfigManager;
    sf::RenderWindow *m_pMainWindow{};
    int m_iBlockSize{};
    sf::Vector2f sidebarPos;
    sf::Vector2f sidebarSize;
public:
    Player() {
        m_pAssetsManager = engine::AssetsManager::getInstance();
        m_pMemoryManager = engine::MemoryManager::getInstance();
        m_pCameraManager = engine::CameraManager::getInstance();
        m_pConfigManager = engine::ConfigManager::getInstance();


    }

    void initialize() override {
        m_pMainWindow = m_pMemoryManager->getMainWindow();
        m_pSprite = m_pAssetsManager->getSprite("player01");
        m_pSprite->setPosition(getPosition());

        json gameConfig = m_pConfigManager->getJson("game_config");
        m_iBlockSize = gameConfig["block_size"];
        sidebarSize.x = gameConfig["sidebar_size"][0];
        sidebarSize.y = gameConfig["sidebar_size"][1];

        sidebarPos = {1920 - (float) sidebarSize.x, 1080 - (float) sidebarSize.y};
    }

    void draw(sf::RenderTarget &rt) override {
        rt.draw(*m_pSprite);
    }

    void checkCollisionWithSidebar(const sf::Vector2f &newPosition) {
        if (newPosition.x + m_iBlockSize >= sidebarPos.x && newPosition.y + m_iBlockSize >= sidebarPos.y) {
            hide();
        } else {
            show();
        }
    }


    void update() override {

        sf::Vector2i mousePosition;
        sf::Vector2f newPosition;

        sf::Vector2f cameraShift = m_pCameraManager->getInvertedCameraPosition();

        mousePosition = sf::Mouse::getPosition(*m_pMainWindow);

        mousePosition.x -= (int) cameraShift.x % m_iBlockSize;
        mousePosition.y -= (int) cameraShift.y % m_iBlockSize;

        newPosition.x = mousePosition.x - mousePosition.x % m_iBlockSize + (int) cameraShift.x % m_iBlockSize;
        newPosition.y = mousePosition.y - mousePosition.y % m_iBlockSize + (int) cameraShift.y % m_iBlockSize;

        m_pSprite->setPosition(newPosition);

        checkCollisionWithSidebar(newPosition);
    }


};

class Map {
private:
    std::vector<std::vector<str>> m_vcLoadedMap;
    int m_loadedMapSize = 0;
    engine::ConfigManager *m_pConfigManager;
    engine::AssetsManager *m_pAssetsManager;
    engine::CameraManager *m_pCameraManager;
    std::map<str, engine::SpritePtr> m_loadedSprites;
    sf::Vector2f m_StoragePos;
    int m_iBlockSize = 0;
    sf::Vector2i m_screenResolution;
public:

    void load(const str &filePath) {
        m_vcLoadedMap.clear();
        std::ifstream mapFile;
        mapFile.open(filePath);
        str line;
        std::vector<str> tmpLineVector;
        m_loadedMapSize = 0;
        int x = 0, y = 0;

        while (std::getline(mapFile, line)) {
            x = 0;
            tmpLineVector.clear();
            for (auto const &id: splitString(line, '+')) {
                tmpLineVector.push_back(id);
                m_loadedMapSize++;

                if (id == "100") {
                    m_StoragePos.x = x;
                    m_StoragePos.y = y;
                }
                x += m_iBlockSize;
            }
            m_vcLoadedMap.push_back(tmpLineVector);
            y += m_iBlockSize;
        }
        mapFile.close();
        m_pCameraManager->setMaxPosition({(float) x - m_screenResolution.x,
                                          (float) y - m_screenResolution.y});
        m_pCameraManager->setMinPosition({0, 0});
    }


    sf::Vector2f getStoragePos() {
        return m_StoragePos;
    }

    void initialize() {

        m_pConfigManager = engine::ConfigManager::getInstance();
        m_pAssetsManager = engine::AssetsManager::getInstance();
        m_pCameraManager = engine::CameraManager::getInstance();

        m_iBlockSize = m_pConfigManager->getJson("game_config")["block_size"];
        json windowConfig = m_pConfigManager->getJson("window_config");
        m_screenResolution.x = windowConfig["width"];
        m_screenResolution.y = windowConfig["height"];

        load("../resources/maps/map_1.mp");

        json resources = m_pConfigManager->getJson("resources");
        std::map<str, str> resourcesIdsNames = resources["ids"];

        for (auto &idsNamesPairs: resourcesIdsNames) {
            m_loadedSprites[idsNamesPairs.first] = m_pAssetsManager->getSprite(idsNamesPairs.second);
        }


    }

    std::vector<std::vector<str>> &getLoadedMap() {
        return m_vcLoadedMap;
    }

    void draw(sf::RenderTarget &rt) {
        auto cameraPosition = m_pCameraManager->getCameraPosition();

        int x = 0, y = 0;
        for (const auto &lineVec: m_vcLoadedMap) {
            x = 0;
            if (cameraPosition.y + m_screenResolution.y < y) break;
            if (y < cameraPosition.y - m_iBlockSize) {
                y += m_iBlockSize;
                continue;
            }

            for (const auto &id: lineVec) {
                if (cameraPosition.x + m_screenResolution.x < x) break;

                if (x < cameraPosition.x - m_iBlockSize) {
                    x += m_iBlockSize;
                    continue;
                }

                if (id == "100") {
                    x += m_iBlockSize;
                    continue;
                }
                m_loadedSprites.at(id)->setPosition(x + -cameraPosition.x, y + -cameraPosition.y);
                rt.draw(*m_loadedSprites.at(id));
                x += m_iBlockSize;
            }
            y += m_iBlockSize;
        }

    }

    void update() {

    }
};

class Minerals {


private:
    std::map<str, engine::SpritePtr> m_mpLoadedSprites;
    engine::ConfigManager *m_pConfigManager;
    engine::AssetsManager *m_pAssetsManager;
    engine::CameraManager *m_pCameraManager;

    std::vector<std::vector<str>> m_vcLoadedMap;
    std::map<str, std::vector<sf::Vector2f>> m_mpMineralsMap;

    json m_mineralsData;

public:
    void initialize() {
        m_pConfigManager = engine::ConfigManager::getInstance();
        m_pAssetsManager = engine::AssetsManager::getInstance();
        m_pCameraManager = engine::CameraManager::getInstance();

        m_mineralsData = m_pConfigManager->loadJson("../resources/config/minerals.json", "minerals");

        for (const auto &mineralName: m_mineralsData["names"]) {
            m_mpLoadedSprites[mineralName] = m_pAssetsManager->getSprite(mineralName);
        }

    }

    void generate() {
        srand(time(nullptr));

        json names = m_mineralsData["names"];
        std::vector<str> prohibitedPlaces = m_mineralsData["prohibited_places"];

        json generatingProperties;
        int veinSize = 0;
        sf::Vector2i mapSize;
        sf::Vector2f startPosition;

        mapSize.y = m_vcLoadedMap.size();
        mapSize.x = m_vcLoadedMap.at(0).size();

        for (int i = 0; i <= 5; i++)
            for (str mineralName: names) {
                generatingProperties = m_mineralsData["generating"][mineralName];

                int maxSize = generatingProperties["max_size"];
                int minSize = generatingProperties["min_size"];
                int probability = generatingProperties["probability"];

                if (rand() % 30 + 1 <= probability) {
                    std::cout << "Generating " << mineralName << std::endl;

                    startPosition.x = rand() % mapSize.x + 1;
                    startPosition.y = rand() % mapSize.y + 1;
                    std::cout << startPosition.x << " " << startPosition.y << std::endl;

                    str id = m_vcLoadedMap.at(startPosition.y - 1).at(startPosition.x - 1);

                    if (find(prohibitedPlaces.begin(), prohibitedPlaces.end(), id) != prohibitedPlaces.end()) {
                        continue;
                    }

                    startPosition.x *= 60;
                    startPosition.y *= 60;
                    m_mpMineralsMap[mineralName].push_back(startPosition);


                }
            }
    }

    void setLoadedMap(const std::vector<std::vector<str>> &loadedMap) {
        m_vcLoadedMap = loadedMap;
    }

    void draw(sf::RenderTarget &rt) {
        auto cameraPosition = m_pCameraManager->getInvertedCameraPosition();
        for (str mineralName: m_mineralsData["names"]) {
            for (auto const &pos: m_mpMineralsMap[mineralName]) {
                engine::SpritePtr sprite = m_mpLoadedSprites[mineralName];
                sprite->setPosition({pos.x + cameraPosition.x, pos.y + cameraPosition.y});
                rt.draw(*sprite);
            }
        }
    }

    void update() {

    }
};

class Main : public engine::Scene {
private:
    std::shared_ptr<SideBar> m_pSideBar;
    std::shared_ptr<Storage> m_pStorage;
    std::shared_ptr<Player> m_pPlayer;
    engine::ConfigManager *m_pConfigManager;
    engine::EntitiesManager *m_pEntitiesManager;
    engine::AssetsManager *m_pAssetsManager;
    Map m_map;
    Minerals m_minerals;
public:
    void onInitializeScene() override {

        m_map.initialize();
        m_minerals.setLoadedMap(m_map.getLoadedMap());
        m_minerals.initialize();
        m_minerals.generate();

        json gameConfig = m_pConfigManager->getJson("game_config");
        int blockSize = gameConfig["block_size"];
        json sidebarSize = gameConfig["sidebar_size"];



        m_pSideBar = std::make_shared<SideBar>();
        m_pStorage = std::make_shared<Storage>();
        m_pPlayer = std::make_shared<Player>();

        m_pSideBar->setPosition(1920 - (int) sidebarSize[0], 1080 - (int) sidebarSize[1]);
        m_pStorage->setPosition(m_map.getStoragePos());
        m_pPlayer->setPosition(0, 0);


        m_pEntitiesManager->attach(m_pStorage);
        m_pEntitiesManager->attach(m_pSideBar);
        m_pEntitiesManager->attach(m_pPlayer);


    }

    void onUpdate() override {
        m_map.update();
        m_minerals.update();


    }

    void onDraw(sf::RenderTarget &rt) override {
        m_map.draw(rt);
        m_minerals.draw(rt);
    }

    void onLoadResources() override {
        m_pConfigManager = engine::ConfigManager::getInstance();
        m_pEntitiesManager = engine::EntitiesManager::getInstance();
        m_pAssetsManager = engine::AssetsManager::getInstance();

        m_pConfigManager->loadJson("../resources/config/game.json", "game_config");
        json resources = m_pConfigManager->loadJson("../resources/config/resources.json", "resources");

        json dirs = resources["dirs"];

        for (const auto &path: dirs) {
            m_pAssetsManager->loadTexturesFromDir(path);
        }


        m_map.initialize();
        m_minerals.initialize();
    }


};

class Shop : public engine::Scene {

};

#endif //MYMINDUSTRY_SCENES_H
