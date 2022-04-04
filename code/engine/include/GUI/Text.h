//
// Created by crazy on 04.04.2022.
//

#ifndef MYMINDUSTRY_TEXT_H
#define MYMINDUSTRY_TEXT_H

#include <SFML/Graphics.hpp>
#include "../types.h"
#include "../Entity.h"

namespace engine {
    class Text : public Entity {
    private:
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

        bool m_bJustHovered = false; // for optimization

    public:
        
    };
}


#endif //MYMINDUSTRY_TEXT_H
