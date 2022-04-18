//
// Created by crazy on 02.04.2022.
//

#ifndef MYMINDUSTRY_MEMORYMANAGER_H
#define MYMINDUSTRY_MEMORYMANAGER_H

#include "LoggingManager.h"
#include "SFML/Graphics.hpp"
#include "variables/SmartStr.h"
#include <variant>

namespace engine {
    class MemoryManager {
    private:
        LoggingManager *m_pLoggingManager;

        sf::RenderWindow *m_pMainWindow{};

        std::map<str, void *> m_mpVariables;

        std::vector<int> m_vcSignals;

    protected:
        static MemoryManager *s_pSelf;

        MemoryManager();

        virtual ~MemoryManager() = default;

    public:
        static MemoryManager *getInstance();

        static bool deleteInstance();

        void setMainWindow(sf::RenderWindow *window);

        sf::RenderWindow *getMainWindow();

        void updateVariables();

        void addVariable(const str &name, SmartVariable *variable);

        void *getVariable(const str &name);

        SmartStr *getStringVariable(const str &name);

        void clearVariables();

        void pushSignal(int signal);

        std::vector<int> &getSignals();

        void clearSignals();
    };

    enum signals {
        EXIT = 0,
    };

}


#endif //MYMINDUSTRY_MEMORYMANAGER_H
