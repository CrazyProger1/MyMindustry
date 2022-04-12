//
// Created by crazy on 07.04.2022.
//

#include "../../include/managers/CameraManager.h"


namespace engine {

    CameraManager *CameraManager::s_pSelf = nullptr;

    CameraManager::CameraManager() {
        m_pLoggingManager = LoggingManager::getInstance();

        m_pLoggingManager->logInfo("CameraManager initialized");
    }


    CameraManager *CameraManager::getInstance() {
        if (!s_pSelf) {
            s_pSelf = new CameraManager();
        }

        return s_pSelf;
    }

    bool CameraManager::deleteInstance() {
        if (s_pSelf) {
            delete s_pSelf;
            s_pSelf = nullptr;
            return true;
        }
        return false;
    }

    void CameraManager::reset() {
        m_position.x = 0;
        m_position.y = 0;
        m_fScaling = 0;
    }

    void CameraManager::move(float xOffset, float yOffset) {
        if (m_position.x + xOffset <= m_maxPosition.x && m_position.x + xOffset >= m_minPosition.x) {
            m_position.x += xOffset;
            m_bIsCameraShiftingNow = true;
        } else {
            m_currentTickShift.x = 0;
        }

        if (m_position.y + yOffset <= m_maxPosition.y && m_position.y + yOffset >= m_minPosition.y) {
            m_position.y += yOffset;
            m_bIsCameraShiftingNow = true;
        } else {
            m_currentTickShift.y = 0;
        }


    }

    void CameraManager::move(const sf::Vector2f &offset) {

        if (m_position.x + offset.x <= m_maxPosition.x && m_position.x + offset.x >= m_minPosition.x) {
            m_position.x += offset.x;
            m_bIsCameraShiftingNow = true;
        } else {
            m_currentTickShift.x = 0;

        }

        if (m_position.y + offset.y <= m_maxPosition.y && m_position.y + offset.y >= m_minPosition.y) {
            m_position.y += offset.y;
            m_bIsCameraShiftingNow = true;
        } else {
            m_currentTickShift.y = 0;
        }
    }


    void CameraManager::handleSFMLEvent(sf::Event &event) {


        if (event.type == sf::Event::KeyPressed)
            if (std::find(m_vcPressedKeys.begin(), m_vcPressedKeys.end(), event.key.code) == m_vcPressedKeys.end())
                m_vcPressedKeys.push_back(event.key.code);

        if (event.type == sf::Event::KeyReleased)
            m_vcPressedKeys.erase(std::remove(m_vcPressedKeys.begin(), m_vcPressedKeys.end(), event.key.code),
                                  m_vcPressedKeys.end());
    }


    sf::Vector2f CameraManager::getCurrentTickShift() {
        return m_currentTickShift;
    }

    bool CameraManager::isCameraShiftingNow() {
        bool buffer = m_bIsCameraShiftingNow;
        m_bIsCameraShiftingNow = false;
        return buffer;
    }

    void CameraManager::update() {
        m_currentTickShift.x = 0;
        m_currentTickShift.y = 0;

        for (auto pressedKey: m_vcPressedKeys)
            switch (pressedKey) {
                case sf::Keyboard::W:
                    m_currentTickShift.y = -m_oneTickShift;
                    break;
                case sf::Keyboard::S:
                    m_currentTickShift.y = m_oneTickShift;
                    break;
                case sf::Keyboard::A:
                    m_currentTickShift.x = -m_oneTickShift;
                    break;
                case sf::Keyboard::D:
                    m_currentTickShift.x = m_oneTickShift;
                    break;
                default:
                    break;
            }

        if (m_currentTickShift.x != 0 || m_currentTickShift.y != 0) {
            move(m_currentTickShift);
        }

    }

    sf::Vector2f CameraManager::getCameraPosition() {
        return m_position;
    }

    sf::Vector2f CameraManager::getInvertedCameraPosition() const {
        return {-m_position.x, -m_position.y};
    }

    void CameraManager::setMaxPosition(const sf::Vector2f &position) {
        m_maxPosition = position;
    }

    void CameraManager::setMinPosition(const sf::Vector2f &position) {
        m_minPosition = position;
    }


}