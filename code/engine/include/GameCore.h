//
// Created by crazy on 01.04.2022.
//

#ifndef MYMINDUSTRY_GAMECORE_H
#define MYMINDUSTRY_GAMECORE_H

#include <SFML/Graphics.hpp>
#include "managers/LoggingManager.h"
#include "managers/ScenesManager.h"
#include "managers/MemoryManager.h"
#include "managers/AssetsManager.h"
#include "managers/CameraManager.h"
#include "managers/ConfigManager.h"

namespace engine {
    class GameCore {
    private:
        sf::RenderWindow *m_pMainWindow = nullptr;
        LoggingManager *m_pLoggingManager;
        ScenesManager *m_pScenesManager;
        EntitiesManager *m_pEntitiesManager;
        MemoryManager *m_pMemoryManager;
        AssetsManager *m_pAssetsManager;
        CameraManager *m_pCameraManager;
        ConfigManager *m_pConfigManager;


        bool m_bDebug = false;

        void handleSFMLEvents();

        void tick();

        void updateSignals();

    public:
        GameCore();

        void setMainWindow(sf::RenderWindow *window);

        void setDebug(bool debug = false);

        void setActiveScene(int id);

        void addScene(int id, const ScenePtr &scene);

        void run();

        void terminate();

        void draw();

        void update();

        virtual void onDraw(sf::RenderTarget &rt) {};

        virtual void onUpdate() {};

        virtual void onTerminate() {};

        virtual void onSFMLEvent(sf::Event &event) {};

    };
}


#endif //MYMINDUSTRY_GAMECORE_H
