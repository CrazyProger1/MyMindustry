//
// Created by crazy on 05.04.2022.
//

#include "../../include/GUI/ButtonStyle.h"


namespace engine {
    ButtonStyle::ButtonStyle(const sf::Vector2f &size,
                             const sf::Color &color,
                             const sf::Color &hoverColor,
                             const sf::Vector2f &textOffset,
                             const sf::Vector2f &imageOffset,
                             int borderWidth,
                             const sf::Color &borderColor,
                             bool centerText,
                             bool centerImage,
                             int cornerRadius,
                             bool isDeactivated,
                             const sf::Color &deactivatedColor) {
        m_size = size;
        m_color = color;
        m_hoverColor = hoverColor;
        m_textOffset = textOffset;
        m_imageOffset = imageOffset;
        m_iBorderWidth = borderWidth;
        m_borderColor = borderColor;
        m_bCenterText = centerText;
        m_bCenterImage = centerImage;
        m_iCornerRadius = cornerRadius;
        m_bIsDeactivated = isDeactivated;
        m_deactivatedColor = deactivatedColor;


    }


    sf::Vector2f &ButtonStyle::getSize() {
        return m_size;
    }

    sf::Vector2f &ButtonStyle::getTextOffset() {
        return m_textOffset;
    }

    int ButtonStyle::getBorderWidth() const {
        return m_iBorderWidth;
    }

    int ButtonStyle::getCornerRadius() const {
        return m_iCornerRadius;
    }

    sf::Color &ButtonStyle::getColor() {
        return m_color;
    }

    sf::Color &ButtonStyle::getHoverColor() {
        return m_hoverColor;
    }

    sf::Color &ButtonStyle::getBorderColor() {
        return m_borderColor;
    }

    sf::Color &ButtonStyle::getDeactivatedColor() {
        return m_deactivatedColor;
    }

    sf::Vector2f &ButtonStyle::getImageOffset() {
        return m_imageOffset;
    }


    bool ButtonStyle::isDeactivated() const {
        return m_bIsDeactivated;
    }

    bool ButtonStyle::centerText() const {
        return m_bCenterText;
    }

    bool ButtonStyle::centerImage() const {
        return m_bCenterImage;
    }
}