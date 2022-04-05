//
// Created by crazy on 05.04.2022.
//

#include "../../include/GUI/TextStyle.h"


namespace engine {
    TextStyle::TextStyle(const str &fontFilepath,
                         int textSFMLStyle,
                         int fontSize,
                         int underlineOffset,
                         int underlineWidth,
                         const sf::Color &textColor,
                         const sf::Color &underlineColor,
                         const sf::Color &textHoverColor,
                         const sf::Color &underlineHoverColor) {
        m_sFontFilepath = fontFilepath;
        m_uTextSFMLStyle = textSFMLStyle;
        m_iFontSize = fontSize;
        m_iUnderlineOffset = underlineOffset;
        m_iUnderlineWidth = underlineWidth;
        m_textColor = textColor;
        m_underlineColor = underlineColor;
        m_textHoverColor = textHoverColor;
        m_underlineHoverColor = underlineHoverColor;
    }

    str &TextStyle::getFontFilepath() {
        return m_sFontFilepath;
    }

    unsigned int TextStyle::getTextSFMLStyle() const {
        return m_uTextSFMLStyle;
    }

    int TextStyle::getFontSize() const {
        return m_iFontSize;
    }

    int TextStyle::getUnderlineOffset() const {
        return m_iUnderlineOffset;
    }

    int TextStyle::getUnderlineWidth() const {
        return m_iUnderlineWidth;
    }

    sf::Color &TextStyle::getTextColor() {
        return m_textColor;
    }

    sf::Color &TextStyle::getTextHoverColor() {
        return m_textHoverColor;
    }

    sf::Color &TextStyle::getUnderlineColor() {
        return m_underlineColor;
    }

    sf::Color &TextStyle::getUnderlineHoverColor() {
        return m_underlineHoverColor;
    }
}