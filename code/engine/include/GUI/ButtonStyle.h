//
// Created by crazy on 05.04.2022.
//

#ifndef MYMINDUSTRY_BUTTONSTYLE_H
#define MYMINDUSTRY_BUTTONSTYLE_H

#include <SFML/Graphics.hpp>

namespace engine {
    struct ButtonStyle {
    private:
        bool m_bIsDeactivated = false;

        sf::Vector2f m_size;
        sf::Vector2f m_textOffset;
        sf::Vector2f m_imageOffset;

        int m_iBorderWidth = 0;
        int m_iCornerRadius = 0;

        sf::Color m_color = {50, 200, 0};
        sf::Color m_hoverColor = {255, 0, 0};
        sf::Color m_borderColor = {0, 0, 150};
        sf::Color m_deactivatedColor = {100, 100, 100};

        bool m_bCenterText = false;
        bool m_bCenterImage = false;
    public:

        explicit ButtonStyle(
                const sf::Vector2f &size,
                const sf::Color &color = {250, 0, 100},
                const sf::Color &hoverColor = {0, 250, 0},
                const sf::Vector2f &textOffset = {0, 0},
                const sf::Vector2f &imageOffset = {0, 0},
                int borderWidth = 0,
                const sf::Color &borderColor = {100, 100, 100},
                bool centerText = false,
                bool centerImage = false,
                int cornerRadius = 0,
                bool isDeactivated = false,
                const sf::Color &deactivatedColor = {100, 100, 100}
        );


        sf::Vector2f &getSize();

        sf::Vector2f &getTextOffset();

        sf::Vector2f &getImageOffset();

        [[nodiscard]] int getBorderWidth() const;

        [[nodiscard]] int getCornerRadius() const;

        sf::Color &getColor();

        sf::Color &getHoverColor();

        sf::Color &getBorderColor();

        sf::Color & getDeactivatedColor();


        [[nodiscard]] bool isDeactivated() const;


        [[nodiscard]] bool centerText() const;

        [[nodiscard]] bool centerImage() const;


    };
}


#endif //MYMINDUSTRY_BUTTONSTYLE_H
