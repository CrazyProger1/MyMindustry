//
// Created by crazy on 11.04.2022.
//

#ifndef MYMINDUSTRY_CONFIGMANAGER_H
#define MYMINDUSTRY_CONFIGMANAGER_H

#include <map>
#include "LoggingManager.h"

namespace engine {
    class ConfigManager {
    private:
        LoggingManager *m_pLoggingManager;

        std::map<str, json> m_mpConfigs;

        std::map<str, std::map<str, str>> m_mpLoadedLangPack;

    protected:
        static ConfigManager *s_pSelf;

        ConfigManager();

        virtual ~ConfigManager() = default;

    public:
        static ConfigManager *getInstance();

        static bool deleteInstance();

        json &loadJson(const str &filePath, const str &name);

        json &getJson(const str &name);

        void unloadJson(const str &name);

        void loadLanguagePack(const str &filePath, const str &langName = "en");

        str &getTranslation(const str &chapter, const str &name);

    };

}


#endif //MYMINDUSTRY_CONFIGMANAGER_H
