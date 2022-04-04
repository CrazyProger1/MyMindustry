//
// Created by crazy on 02.04.2022.
//

#ifndef MYMINDUSTRY_ENTITIESMANAGER_H
#define MYMINDUSTRY_ENTITIESMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>
#include "LoggingManager.h"
#include "../Entity.h"

namespace engine {
    class EntitiesManager {
    private:
        LoggingManager *m_pLoggingManager;

        std::map<int, Entity *> m_mpEntities;

        int m_iCurrentEntityId = 0;

    protected:
        static EntitiesManager *s_pSelf;

        EntitiesManager();

        virtual ~EntitiesManager() = default;

    public:
        static EntitiesManager *getInstance();

        static bool deleteInstance();

        int attach(Entity *entity);

        void initEntities();

        void drawEntities(sf::RenderTarget &rt);

        void updateEntities();

        void handleSFMLEvent(sf::Event &event);

        void clear();
    };
}


#endif //MYMINDUSTRY_ENTITIESMANAGER_H
