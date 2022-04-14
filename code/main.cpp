#include <SFML/Graphics.hpp>

#include "game/game.h"


int main() {
    Game game;
    game.setDebug(true);
    auto pConfigManager = engine::ConfigManager::getInstance();
    json windowConfig = pConfigManager->loadJson("../resources/config/window.json",
                                                 "window");


    int windowStyle = sf::Style::Default;
    if (windowConfig["fullscreen"]) {
        windowStyle = sf::Style::Fullscreen;
    }
    sf::RenderWindow window(sf::VideoMode(windowConfig["width"],
                                          windowConfig["height"]),
                            windowConfig["title"],
                            windowStyle);


    game.setMainWindow(&window);

//    game.addScene(1, std::make_shared<Menu>());
//    game.addScene(2, std::make_shared<Main>());
//    game.addScene(3, std::make_shared<Shop>());
    game.addScene(1, std::make_shared<MapEditorScene>());
    game.setActiveScene(1);


    game.run();
    game.terminate();
    return 0;
}

//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <string>
//#include <chrono>
//#include <fstream>
//#include <regex>
//#include <vector>
//
//std::chrono::high_resolution_clock::time_point start;
//std::chrono::high_resolution_clock::time_point end;
//float fps;
//std::vector<std::vector<std::string>> map;
//int blockSize = 60;
//
//
//std::vector<std::string> splitString(const std::string &str, char delim = '\n') {
//    std::vector<std::string> tokens;
//
//    std::stringstream ss(str);
//    std::string token;
//    while (std::getline(ss, token, delim)) {
//        tokens.push_back(token);
//    }
//
//    return tokens;
//}
//
//void loadMap(const std::string &filePath) {
//    map.clear();
//    std::ifstream mapFile;
//    mapFile.open(filePath);
//    std::string line;
//    std::vector<std::string> tmpLineVector;
//    int x = 0, y = 0;
//
//    while (std::getline(mapFile, line)) {
//        x = 0;
//        tmpLineVector.clear();
//        for (auto const &id: splitString(line, '+')) {
//            tmpLineVector.push_back(id);;
//            x += blockSize;
//        }
//        map.push_back(tmpLineVector);
//        y += blockSize;
//    }
//    mapFile.close();
//}
//
//class method1 {
//private:
//    std::vector<sf::Sprite *> sprites;
//
//    sf::Texture texture;
//public:
//    method1() {
//        texture.loadFromFile("../resources/sprites/floors/earth_floor01.jpg");
//        int spriteCounter = 0;
//        int x = 0, y = 0;
//        for (auto &line: map) {
//            x = 0;
//            for (auto &blockId: line) {
//                auto *sprite = new sf::Sprite;
//                sprite->setPosition(x * blockSize, y * blockSize);
//                sprite->setTexture(texture);
//                sprite->rotate(90);
//                sprites.emplace_back(sprite);
//                spriteCounter++;
//                x++;
//            }
//            y++;
//        }
//
//        std::cout << "Sprites: " << spriteCounter << std::endl;
//    }
//
//    void draw(sf::RenderTarget &rt) {
//        for (auto &sprite: sprites) {
//            rt.draw(*sprite);
//        }
//    }
//};
//
//class method2 {
//private:
//    sf::Texture texture;
//    sf::Sprite *sprite = new sf::Sprite;
//public:
//    method2() {
//        texture.loadFromFile("../resources/sprites/floors/earth_floor01.jpg");
//        sprite->setTexture(texture);
//    }
//
//    void draw(sf::RenderTarget &rt) {
//        int x = 0, y = 0;
//        for (auto &line: map) {
//            x = 0;
//            for (auto &blockId: line) {
//                sprite->setPosition(x * blockSize, y * blockSize);
//                sprite->rotate(90);
//                rt.draw(*sprite);
//                x++;
//            }
//            y++;
//        }
//    }
//};
//
//int main() {
//    loadMap("../resources/maps/map_2.mp");
//
//    method1 method_1;
//    method2 method_2;
//
//    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
//
//    while (window.isOpen()) {
//        sf::Event event{};
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//
//        start = std::chrono::high_resolution_clock::now();
//
//        window.clear(sf::Color::Black);
//        // window.draw, etc.
//        method_1.draw(window);
////        method_2.draw(window);
//        window.display();
//
//        end = std::chrono::high_resolution_clock::now();
//
//        fps = (float) 1e9 / (float) std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//
//        std::cout << fps << std::endl;
//    }
//
//    return 0;
//}