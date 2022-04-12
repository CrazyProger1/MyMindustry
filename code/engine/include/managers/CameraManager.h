//
// Created by crazy on 07.04.2022.
//

#ifndef MYMINDUSTRY_CAMERAMANAGER_H
#define MYMINDUSTRY_CAMERAMANAGER_H

#include <SFML/Graphics.hpp>
#include "MemoryManager.h"
#include "LoggingManager.h"

namespace engine {
    class CameraManager {
    private:

        LoggingManager *m_pLoggingManager;
//        sf::Vector2f m_position;
        sf::Vector2f m_position;
        sf::Vector2u m_resolution;
        sf::Vector2f m_currentTickShift;
        float m_fScaling = 0;
        float m_oneTickShift = 1;
        int m_blockSize = 60;
        bool m_roundToBlockSize;
        bool m_bIsCameraShiftingNow = false;
        std::vector<int> m_vcPressedKeys;
        sf::Vector2f m_maxPosition;
        sf::Vector2f m_minPosition;

        str m_moveMode = "MAN";
        //// WASD(Keyboard WASD) + MAN(Manually) + ARRS(Keyboard Arrays) + NUM(Keyboard numbers)


    protected:
        static CameraManager *s_pSelf;

        CameraManager();

        virtual ~CameraManager() = default;

    public:
        static CameraManager *getInstance();

        static bool deleteInstance();

        void move(float xOffset, float yOffset);

        void move(const sf::Vector2f &offset);

        void update();

        void reset();

        void handleSFMLEvent(sf::Event &event);

        bool isCameraShiftingNow();

        sf::Vector2f getCurrentTickShift();

        sf::Vector2f getCameraPosition();

        [[nodiscard]] sf::Vector2f getInvertedCameraPosition() const;

        void setMaxPosition(const sf::Vector2f &position);

        void setMinPosition(const sf::Vector2f &position);


    };
}


#endif //MYMINDUSTRY_CAMERAMANAGER_H
