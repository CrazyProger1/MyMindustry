//
// Created by crazy on 02.04.2022.
//

#ifndef MYMINDUSTRY_SCENESMANAGER_H
#define MYMINDUSTRY_SCENESMANAGER_H

#include <map>
#include "LoggingManager.h"
#include "../Scene.h"
#include <SFML/Graphics.hpp>

namespace engine {
    class ScenesManager {

    private:
        LoggingManager *m_pLoggingManager;

        Scene *m_pActiveScene = nullptr;

        std::map<int, Scene *> m_mpScenes;

    protected:
        static ScenesManager *s_pSelf;

        ScenesManager();

        virtual ~ScenesManager() = default;

    public:
        static ScenesManager *getInstance();

        static bool deleteInstance();

        void setActiveScene(int id);

        void addScene(int id, Scene *scene);

        void updateScene();

        void destroyActiveScene();

        void drawScene(sf::RenderWindow &window);

        void handleSFMLEvent(sf::Event &event);

    };

}


#endif //MYMINDUSTRY_SCENESMANAGER_H
