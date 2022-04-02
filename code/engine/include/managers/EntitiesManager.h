//
// Created by crazy on 02.04.2022.
//

#ifndef MYMINDUSTRY_ENTITIESMANAGER_H
#define MYMINDUSTRY_ENTITIESMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>
#include "LoggingManager.h"

namespace engine {
    class EntitiesManager {
    private:
        LoggingManager *m_pLoggingManager;

    protected:
        static EntitiesManager *s_pSelf;

        EntitiesManager();

        virtual ~EntitiesManager() = default;

    public:
        static EntitiesManager *getInstance();

        static bool deleteInstance();
    };
}


#endif //MYMINDUSTRY_ENTITIESMANAGER_H
