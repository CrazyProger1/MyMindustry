//
// Created by crazy on 04.04.2022.
//

#ifndef MYMINDUSTRY_BUTTON_H
#define MYMINDUSTRY_BUTTON_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Text.h"
#include "Image.h"
#include "ButtonStyle.h"

namespace engine {

    class Button : public Entity {
    private:
        sf::RenderWindow *m_pMainWindow;

        bool m_bIsDeactivated = false;

        sf::Vector2f m_size;
        sf::Vector2f m_textOffset;
        sf::Vector2f m_imageOffset;

        int m_iBorderWidth = 0;
        int m_iCornerRadius = 0;

        sf::RectangleShape m_mainRect;
        sf::RectangleShape m_sideRect;
        sf::CircleShape m_cornerCircle;

        sf::RectangleShape m_borderRect;
        sf::RectangleShape m_sideBorderRect;
        sf::CircleShape m_cornerBorderCircle;

        sf::Color m_color = {50, 200, 0};
        sf::Color m_hoverColor = {255, 0, 0};
        sf::Color m_borderColor = {0, 0, 150};
        sf::Color m_deactivatedColor = {100, 100, 100};

        bool m_bIsClicked = false;
        bool m_bIsHovered = false;

        bool m_bCenterText = false;
        bool m_bIsTextSet = false;

        bool m_bCenterImage = false;
        bool m_bIsImageSet = false;

        TextPtr m_pText;
        sf::Color m_textColor;
        sf::Color m_textHoverColor;

        ImagePtr m_pImage;


        bool m_bJustHovered = false; // for optimization

        void centralizeText();

        void centralizeImage();


        void checkClick(sf::Event &event);

        void checkHover();

        void drawBorder(sf::RenderTarget &rt);

    public:
        Button();

        explicit Button(const sf::Vector2f &size,
                        const sf::Color &color = {250, 0, 100},
                        const sf::Color &hoverColor = {0, 250, 0},
                        TextPtr text = nullptr,
                        ImagePtr image = nullptr,
                        const sf::Vector2f &textOffset = {0, 0},
                        const sf::Vector2f &imageOffset = {0, 0},
                        int borderWidth = 0,
                        const sf::Color &borderColor = {100, 100, 100},
                        bool centerText = false,
                        bool centerImage = false,
                        int cornerRadius = 0
        );

        void initialize() override;


        void setSize(const sf::Vector2f &size) override;

        void setSize(float w, float h) override;

        void setTextOffset(const sf::Vector2f &offset);

        void setImageOffset(const sf::Vector2f &offset);

        void setBorderWidth(int width);

        void setColor(const sf::Color &color);

        void setDeactivatedColor(const sf::Color &color);

        void setHoverColor(const sf::Color &color);

        void setBorderColor(const sf::Color &color);

        void setCornerRadius(int radius);

        void setCenteringText(bool center = true);

        void setCenteringImage(bool center = true);

        void setText(const TextPtr &text);

        void setImage(Image &image);

        void setImage(const ImagePtr &image);

        void setStyle(ButtonStyle &buttonStyle);


        bool isClicked();

        bool isHovered() const;


        sf::Vector2f getSize();


        void activate();

        void deactivate();


        void draw(sf::RenderTarget &rt) override;

        void handleSFMLEvent(sf::Event &event) override;

        void update() override;


    };

    typedef std::shared_ptr<Button> ButtonPtr;
}


#endif //MYMINDUSTRY_BUTTON_H
