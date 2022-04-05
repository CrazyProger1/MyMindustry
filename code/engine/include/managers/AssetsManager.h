//
// Created by crazy on 05.04.2022.
//

#ifndef MYMINDUSTRY_ASSETSMANAGER_H
#define MYMINDUSTRY_ASSETSMANAGER_H

#include <SFML/Graphics.hpp>
#include "../types.h"
#include "LoggingManager.h"

namespace engine {
    class AssetsManager {
    private:
        LoggingManager *m_pLoggingManager;
    protected:
        static AssetsManager *s_pSelf;

        AssetsManager();

        virtual ~AssetsManager() = default;

    public:
        static AssetsManager *getInstance();

        static bool deleteInstance();
    };
}


#endif //MYMINDUSTRY_ASSETSMANAGER_H
