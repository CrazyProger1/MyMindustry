//
// Created by crazy on 05.04.2022.
//

#ifndef MYMINDUSTRY_TEXTSTYLE_H
#define MYMINDUSTRY_TEXTSTYLE_H

#include <SFML/Graphics.hpp>
#include "../types.h"

namespace engine {
    struct TextStyle {
        str m_sFontFilepath = "../resources/fonts/arial.ttf";
        unsigned int m_uTextSFMLStyle = 0;
        int m_iFontSize = 20;
        int m_iUnderlineOffset = 5;
        int m_iUnderlineWidth = 0;

        sf::Color m_textColor = {30, 0, 200};
        sf::Color m_underlineColor = {200, 100, 0};
        sf::Color m_textHoverColor = {0, 0, 250};
        sf::Color m_underlineHoverColor = {100, 200, 0};

        explicit TextStyle(
                const str &fontFilepath = "../resources/fonts/arial.ttf",
                int textSFMLStyle = 0,
                int fontSize = 20,
                int underlineOffset = 5,
                int underlineWidth = 0,
                const sf::Color &textColor = {30, 0, 200},
                const sf::Color &underlineColor = {200, 100, 0},
                const sf::Color &textHoverColor = {0, 0, 250},
                const sf::Color &underlineHoverColor = {100, 200, 0}
        );

        str &getFontFilepath();

        [[nodiscard]] unsigned int getTextSFMLStyle() const;

        [[nodiscard]] int getFontSize() const;

        [[nodiscard]] int getUnderlineOffset() const;

        [[nodiscard]] int getUnderlineWidth() const;

        sf::Color &getTextColor();

        sf::Color &getTextHoverColor();

        sf::Color &getUnderlineColor();

        sf::Color &getUnderlineHoverColor();
    };
}


#endif //MYMINDUSTRY_TEXTSTYLE_H
