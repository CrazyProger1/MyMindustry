#include <SFML/Graphics.hpp>
#include "engine/engine.h"
//#include "engine/include/GUI/Button.h"

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
private:
    engine::Entity entity;
public:
    void onUpdate() override {
//        std::cout << "hello" << std::endl;
    }

    void onLoadResources() override {

    }

    void onInitializeScene() override {

        entity.setPosition(10, 10);
        attachEntity(&entity);
    }

    void onSFMLEvent(sf::Event &event) override {
        if (event.type == sf::Event::KeyPressed) {
            engine::ScenesManager::getInstance()->setActiveScene(2);
        }
    }
};

int main() {
    Game game;
    game.setDebug(true);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    game.setMainWindow(&window);

    game.addScene(1, new Menu);
//    game.setActiveScene(1);

    game.run();
    game.terminate();
    return 0;
}