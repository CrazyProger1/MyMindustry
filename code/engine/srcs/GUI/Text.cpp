//
// Created by crazy on 04.04.2022.
//

#include "../../include/GUI/Text.h"

namespace engine {

    void Text::checkClick(sf::Event &event) {
        if (m_bIsHovered)
            if (event.type == sf::Event::MouseButtonPressed) {
                m_bIsClicked = true;
                return;
            }

        m_bIsClicked = false;


    }

    void Text::checkHover() {
        sf::Vector2f size = getFullSize();
        sf::Vector2f pos = getPosition();
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_pMainWindow);

        if (mousePos.x > pos.x && mousePos.x < pos.x + size.x)
            if (mousePos.y > pos.y && mousePos.y < pos.y + size.y) {
                m_bIsHovered = true;
                return;
            }

        m_bIsHovered = false;

    }

    Text::Text() {
        m_pMainWindow = MemoryManager::getInstance()->getMainWindow();
        m_pLoggingManager = LoggingManager::getInstance();
    }

    Text::Text(const str &text,
               const str &fontFilepath,
               int fontSize,
               unsigned int textSFMLStyle,
               int underlineOffset,
               int underlineWidth,
               const sf::Color &textColor,
               const sf::Color &underlineColor,
               const sf::Color &textHoverColor,
               const sf::Color &underlineHoverColor) {
        m_sText = text;
        m_sFontFilepath = fontFilepath;
        m_iFontSize = fontSize;
        m_iUnderlineOffset = underlineOffset;
        m_iUnderlineWidth = underlineWidth;
        m_textColor = textColor;
        m_underlineColor = underlineColor;
        m_textHoverColor = textHoverColor;
        m_underlineHoverColor = underlineHoverColor;
        m_uTextSFMLStyle = textSFMLStyle;

        m_pMainWindow = MemoryManager::getInstance()->getMainWindow();
    }

    void Text::initialize() {
        setType("text");

        sf::Vector2f pos = getPosition();

        if (!m_font.loadFromFile(m_sFontFilepath)) {
            m_pLoggingManager->logError("Font file (" + m_sFontFilepath + ") has not be found");
            throw std::exception();
        }
        m_text.setFont(m_font);
//    m_text.setString(m_sText);
        m_text.setString(sf::String::fromUtf8(m_sText.begin(), m_sText.end()));
        m_text.setCharacterSize(m_iFontSize);
        m_text.setFillColor(m_textColor);
        m_text.setPosition(pos);
        m_text.setStyle(m_uTextSFMLStyle);

        sf::Vector2f size = getSize();


        if (m_iUnderlineWidth > 0) {
            m_underlineRect.setSize({size.x, (float) m_iUnderlineWidth});
            m_underlineRect.setPosition({pos.x + 1, pos.y + size.y + m_iUnderlineOffset});
            m_underlineRect.setFillColor(m_underlineColor);
        }
    }

    void Text::setText(const str &text) {
        if (m_sText == text)
            return;

        m_sText = text;
        initialize();
    }

    void Text::setFont(const str &filepath) {
        m_sFontFilepath = filepath;
        initialize();
    }

    void Text::setFontSize(int size) {
        m_iFontSize = size;
        initialize();
    }

    void Text::setUnderlineOffset(int offset) {
        m_iUnderlineOffset = offset;
        initialize();
    }

    void Text::setUnderlineWidth(int width) {
        m_iUnderlineWidth = width;
        initialize();
    }

    void Text::setTextColor(const sf::Color &color) {
        m_textColor = color;
        initialize();
    }

    void Text::setUnderlineColor(const sf::Color &color) {
        m_underlineColor = color;
        initialize();
    }

    void Text::setTextHoverColor(const sf::Color &color) {
        m_textHoverColor = color;
        initialize();
    }

    void Text::setUnderlineHoverColor(const sf::Color &color) {
        m_underlineHoverColor = color;
        initialize();
    }

    void Text::setTextSFMLStyle(unsigned int style) {
        m_uTextSFMLStyle = style;
        initialize();
    }

    void Text::setStyle(TextStyle &style) {

        m_textColor = style.getTextColor();
        m_underlineColor = style.getUnderlineColor();
        m_textHoverColor = style.getTextHoverColor();
        m_underlineHoverColor = style.getUnderlineHoverColor();
        m_uTextSFMLStyle = style.getTextSFMLStyle();
        m_iUnderlineWidth = style.getUnderlineWidth();
        m_iUnderlineOffset = style.getUnderlineOffset();
        m_iFontSize = style.getFontSize();
        m_sFontFilepath = style.getFontFilepath();
        initialize();
    }


    str &Text::getText() {
        return m_sText;
    }

    sf::Vector2f Text::getSize() {
        float width = m_text.getLocalBounds().width;
        float height = m_iFontSize;
        return {width, height};
    }

    sf::Vector2f Text::getFullSize() {
        float width = m_text.getLocalBounds().width;
        float height = m_iFontSize;
        return {width, height + (float) m_iUnderlineWidth + (float) m_iUnderlineOffset};
    }

    sf::Color &Text::getTextHoverColor() {
        return m_textHoverColor;
    }

    sf::Color &Text::getTextColor() {
        return m_textColor;
    }

    bool Text::isHovered() {
        return m_bIsHovered;
    }

    bool Text::isClicked() {
        bool buff = m_bIsClicked;
        m_bIsClicked = false;
        return buff;
    }

    void Text::draw(sf::RenderTarget &rt) {
        if (m_iUnderlineWidth > 0)
            rt.draw(m_underlineRect);

        rt.draw(m_text);
    }

    void Text::handleSFMLEvent(sf::Event &event) {
        checkClick(event);
    }

    void Text::update() {
        checkHover();

        if (m_bIsHovered) {
            if (!m_bJustHovered) {
                m_text.setFillColor(m_textHoverColor);
                m_underlineRect.setFillColor(m_underlineHoverColor);
                m_bJustHovered = true;
            }

        } else {
            if (m_bJustHovered) {
                m_text.setFillColor(m_textColor);
                m_underlineRect.setFillColor(m_underlineColor);
                m_bJustHovered = false;
            }

        }
    }

}


