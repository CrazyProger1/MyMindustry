//
// Created by crazy on 01.04.2022.
//

#include "../include/GameCore.h"


namespace engine {
    GameCore::GameCore() {
        m_pLoggingManager = LoggingManager::getInstance();
        m_pLoggingManager->clearLog();
        m_pLoggingManager->logInfo("LoggingManager initialized");

        m_pLoggingManager->logInfo("Core (v1) initialized");
        m_pScenesManager = ScenesManager::getInstance();
        m_pEntitiesManager = EntitiesManager::getInstance();
        m_pMemoryManager = MemoryManager::getInstance();
        m_pAssetsManager = AssetsManager::getInstance();
        m_pCameraManager = CameraManager::getInstance();
        m_pConfigManager = ConfigManager::getInstance();
    };


    void GameCore::setMainWindow(sf::RenderWindow *window) {
        m_pMainWindow = window;
        m_pMemoryManager->setMainWindow(window);
        m_pLoggingManager->logInfo("Window is set (" + std::to_string(window->getSize().x)
                                   + "x" + std::to_string(window->getSize().y) + ")");
    }

    void GameCore::setDebug(bool debug) {
        m_bDebug = debug;
        m_pLoggingManager->setPrintOut(m_bDebug);
    }

    void GameCore::setActiveScene(int id) {
        m_pScenesManager->setActiveScene(id);
    }

    void GameCore::addScene(int id, const ScenePtr &scene) {
        m_pScenesManager->addScene(id, scene);

    }

    void GameCore::run() {
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;
        float fps;

        m_pLoggingManager->logInfo("Mainloop ran");
        while (m_pMainWindow->isOpen()) {
            start = std::chrono::high_resolution_clock::now();
            // window.draw, etc.
            tick();
            end = std::chrono::high_resolution_clock::now();

            fps = (float) 1e9 / (float) std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//            std::cout << fps << std::endl;
        }


    }

    void GameCore::terminate() {
        m_pScenesManager->destroyActiveScene();
        onTerminate();
        m_pMainWindow->close();
        m_pLoggingManager->logInfo("Game successfully terminated");

        engine::LoggingManager::deleteInstance();
        engine::EntitiesManager::deleteInstance();
        engine::ScenesManager::deleteInstance();
        exit(0);
    }


    void GameCore::handleSFMLEvents() {
        sf::Event event{};
        while (m_pMainWindow->pollEvent(event)) {

            onSFMLEvent(event);
            m_pScenesManager->handleSFMLEvent(event);

            if (event.type == sf::Event::Closed) {
                m_pLoggingManager->logInfo("Got stop signal");
                terminate();
            }

        }
    }

    void GameCore::tick() {
        update();
        draw();

    }

    void GameCore::draw() {
        m_pMainWindow->clear(sf::Color::Black);

        onDraw(*m_pMainWindow);
        m_pScenesManager->drawScene(*m_pMainWindow);

        m_pMainWindow->display();
    }

    void GameCore::update() {
        handleSFMLEvents();
        onUpdate();
        m_pScenesManager->updateScene();
    }


}