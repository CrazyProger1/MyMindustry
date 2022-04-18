//
// Created by crazy on 15.04.2022.
//

#ifndef MYMINDUSTRY_MAINMENUSCENE_H
#define MYMINDUSTRY_MAINMENUSCENE_H

#include "../engine/engine.h"

class MainMenuScene : public engine::Scene {
private:
    engine::AssetsManager *m_pAssetsManager;
    engine::ConfigManager *m_pConfigManager;
    engine::ScenesManager *m_pScenesManager;
    engine::MemoryManager *m_pMemoryManager;
    std::map<str, engine::ButtonPtr> m_mpButtons;
    json m_jnMenuInfo;
    engine::ImagePtr m_backgroundImage;
public:
    void onLoadResources() override;

    void onInitializeScene() override;

    void onUpdate() override;

};


#endif //MYMINDUSTRY_MAINMENUSCENE_H
