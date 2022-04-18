//
// Created by crazy on 11.04.2022.
//

#include "../../include/managers/ConfigManager.h"

namespace engine {
    ConfigManager *ConfigManager::s_pSelf = nullptr;

    ConfigManager::ConfigManager() {
        m_pLoggingManager = LoggingManager::getInstance();
        m_pLoggingManager->logInfo("ConfigManager initialized");
    }

    bool ConfigManager::deleteInstance() {
        if (s_pSelf) {
            delete s_pSelf;
            s_pSelf = nullptr;
            return true;
        }
        return false;
    }

    ConfigManager *ConfigManager::getInstance() {
        if (!s_pSelf) {
            s_pSelf = new ConfigManager();
        }

        return s_pSelf;
    }

    json &ConfigManager::loadJson(const str &filePath, const str &name) {
        std::ifstream jsonFile;
        jsonFile.open(filePath);
        str buffer, line;
        while (std::getline(jsonFile, line)) {
            buffer += line;
        }
        jsonFile.close();

        m_mpConfigs[name] = nlohmann::json::parse(buffer);
        m_pLoggingManager->logInfo(filePath + " was successfully loaded");

        return m_mpConfigs.at(name);

    }

    void ConfigManager::unloadJson(const str &name) {
        m_mpConfigs[name].clear();
        m_mpConfigs.erase(name);
    }

    json &ConfigManager::getJson(const str &name) {
        return m_mpConfigs.at(name);
    }

    void ConfigManager::loadLanguagePack(const str &filePath, const str &langName) {
        m_mpLoadedLangPack = loadJson(filePath, langName + "_lang");
        m_pLoggingManager->logInfo(filePath + " language pack was successfully loaded");
        unloadJson(langName + "_lang");
    }

    str &ConfigManager::getTranslation(const str &chapter, const str &name) {
        return m_mpLoadedLangPack[chapter][name];
    }
}