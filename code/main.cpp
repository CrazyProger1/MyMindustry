#include <SFML/Graphics.hpp>

#include "game/game.h"


int main() {
    Game game;
    game.setDebug(true);
    auto pConfigManager = engine::ConfigManager::getInstance();
    json windowConfig = pConfigManager->loadJson("../resources/config/window.json",
                                                 "window_config");
    pConfigManager->loadJson("../resources/config/game.json", "game_config");

    int windowStyle = sf::Style::Default;
    if (windowConfig["fullscreen"]) {
        windowStyle = sf::Style::Fullscreen;
    }
    sf::RenderWindow window(sf::VideoMode(windowConfig["width"],
                                          windowConfig["height"]),
                            windowConfig["title"],
                            windowStyle);


    game.setMainWindow(&window);

    game.addScene(1, std::make_shared<Menu>());
    game.addScene(2, std::make_shared<Main>());
    game.addScene(3, std::make_shared<Shop>());
    game.setActiveScene(1);


    game.run();
    game.terminate();
    return 0;
}