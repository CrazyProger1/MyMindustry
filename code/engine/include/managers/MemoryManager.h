//
// Created by crazy on 02.04.2022.
//

#ifndef MYMINDUSTRY_MEMORYMANAGER_H
#define MYMINDUSTRY_MEMORYMANAGER_H

#include "LoggingManager.h"
#include "SFML/Graphics.hpp"

namespace engine {
    class MemoryManager {
    private:
        LoggingManager *m_pLoggingManager;

        sf::RenderWindow *m_pMainWindow{};

    protected:
        static MemoryManager *s_pSelf;

        MemoryManager();

        virtual ~MemoryManager() = default;

    public:
        static MemoryManager *getInstance();

        static bool deleteInstance();

        void setMainWindow(sf::RenderWindow *window);

        sf::RenderWindow *getMainWindow();
    };

}


#endif //MYMINDUSTRY_MEMORYMANAGER_H
