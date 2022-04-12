//
// Created by crazy on 04.04.2022.
//

#ifndef MYMINDUSTRY_TEXT_H
#define MYMINDUSTRY_TEXT_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "../types.h"
#include "../Entity.h"
#include "../managers/MemoryManager.h"
#include "TextStyle.h"

namespace engine {
    class Text : public Entity {
    private:
        sf::RenderWindow *m_pMainWindow;
        LoggingManager *m_pLoggingManager;

        str m_sText;
        str m_sFontFilepath = "../resources/fonts/arial.ttf";
        unsigned int m_uTextSFMLStyle = 0;
        int m_iFontSize = 20;
        int m_iUnderlineOffset = 5;
        int m_iUnderlineWidth = 0;


        sf::Font m_font;
        sf::Text m_text;


        sf::Color m_textColor = {30, 0, 200};
        sf::Color m_underlineColor = {200, 100, 0};
        sf::Color m_textHoverColor = {0, 0, 250};
        sf::Color m_underlineHoverColor = {100, 200, 0};

        sf::RectangleShape m_underlineRect;

        bool m_bIsClicked = false;
        bool m_bIsHovered = false;

        bool m_bJustHovered = false;


        void checkClick(sf::Event &event);

        void checkHover();

    public:
        Text();

        explicit Text(
                const str &text,
                const str &fontFilepath = "../resources/fonts/arial.ttf",
                int fontSize = 20,
                unsigned int textSFMLStyle = 0,
                int underlineOffset = 0,
                int underlineWidth = 0,
                const sf::Color &textColor = {100, 100, 100},
                const sf::Color &underlineColor = {20, 100, 200},
                const sf::Color &textHoverColor = {200, 200, 200},
                const sf::Color &underlineHoverColor = {100, 100, 250}
        );

        void initialize() override;


        void setText(const str &text);

        void setFont(const str &filepath);

        void setFontSize(int size);

        void setUnderlineOffset(int offset);

        void setUnderlineWidth(int width);

        void setTextColor(const sf::Color &color);

        void setUnderlineColor(const sf::Color &color);

        void setTextHoverColor(const sf::Color &color);

        void setUnderlineHoverColor(const sf::Color &color);

        void setTextSFMLStyle(unsigned int style);

        void setStyle(TextStyle &style);


        str &getText();

        sf::Vector2f getSize();

        sf::Vector2f getFullSize();

        sf::Color &getTextHoverColor();

        sf::Color &getTextColor();


        bool isHovered();

        bool isClicked();


        void draw(sf::RenderTarget &rt) override;

        void handleSFMLEvent(sf::Event &event) override;

        void update() override;


    };

    typedef std::shared_ptr<Text> TextPtr;
}


#endif //MYMINDUSTRY_TEXT_H
