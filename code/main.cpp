//#include <SFML/Graphics.hpp>
//#include "game/game.h"
//
//
//int main() {
//    Game game;
//    game.setDebug(true);
//    auto pConfigManager = engine::ConfigManager::getInstance();
//    json windowConfig = pConfigManager->loadJson("../resources/config/window.json",
//                                                 "window");
//
//
//    int windowStyle = sf::Style::Default;
//    if (windowConfig["fullscreen"]) {
//        windowStyle = sf::Style::Fullscreen;
//    }
//
//    sf::ContextSettings settings;
//    settings.antialiasingLevel = 0;
//
//    sf::RenderWindow window(sf::VideoMode(windowConfig["width"],
//                                          windowConfig["height"]),
//                            windowConfig["title"],
//                            windowStyle,
//                            settings);
//
//
//    game.setMainWindow(&window);
//    game.addScene(1, std::make_shared<MainMenuScene>());
//    game.addScene(2, std::make_shared<GameModeSelectionScene>());
//    game.setActiveScene(1);
//
//    game.run();
//    game.terminate();
//    return 0;
//}
//
//

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

inline float angle(sf::Vector2f v) {
    return std::atan2(v.y, v.x);
}

inline std::vector<sf::Vector2f> getCirclePoints(float angle, float radius) {
    std::vector<sf::Vector2f> ret;
    const int maxPoints = 3;
    const float spread = 1.f;
    for (int i = 0; i < maxPoints; ++i) {
        const float a = (angle - spread / 2.f) + (i * spread) / (maxPoints - 1);
        ret.push_back(radius * sf::Vector2f(std::cos(a), std::sin(a)));
    }
    return ret;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "cricl");
    window.setFramerateLimit(60);

    const sf::Vector2f middle = sf::Vector2f(window.getSize()) / 2.f;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        sf::VertexArray arr(sf::LinesStrip);
//        const sf::Vector2f mpos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//        arr.append(sf::Vertex(middle));
        std::vector<sf::Vector2f> pts = getCirclePoints(45, 10);
        std::cout << pts.size() << std::endl;
        for (sf::Vector2f v: pts)
            arr.append(sf::Vertex(v + sf::Vector2f(100, 100)));


        window.draw(arr);
        window.display();
    }
}
