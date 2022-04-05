#include <SFML/Graphics.hpp>

#include "game/game.h"


int main() {
    Game game;
    game.setDebug(true);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window", sf::Style::Fullscreen);
    game.setMainWindow(&window);

    game.addScene(1, new Menu);
    game.addScene(2, new Main);
    game.setActiveScene(1);

    game.run();
    game.terminate();
    return 0;
}