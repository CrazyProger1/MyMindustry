#include <SFML/Graphics.hpp>
#include "engine/engine.h"


class Game : public engine::GameCore {
private:
public:
    void onUpdate() override {

    }

    void onDraw(sf::RenderTarget &rt) override {

    }

    void onTerminate() override {

    }
};


class Menu : public engine::Scene {
    void onUpdate() override {
//        std::cout << "hello" << std::endl;
    }
};

int main() {
    Game game;
    game.setDebug(true);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    game.setMainWindow(&window);

    game.addScene(1, new Menu);
    game.setActiveScene(1);

    game.run();
    game.terminate();
    return 0;
}