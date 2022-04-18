//
// Created by crazy on 15.04.2022.
//

#include "../../include/GUI/ImprovedUsualButton.h"


namespace engine {
    ImprovedUsualButton::ImprovedUsualButton() {
        m_pMainWindow = MemoryManager::getInstance()->getMainWindow();
    }

    ImprovedUsualButton::ImprovedUsualButton(const sf::Vector2f &size,
                                             const sf::Color &color,
                                             const sf::Color &hoverColor,
                                             TextPtr text,
                                             ImagePtr image,
                                             const sf::Vector2f &textOffset,
                                             const sf::Vector2f &imageOffset,
                                             int borderWidth,
                                             const sf::Color &borderColor,
                                             bool centerText,
                                             bool centerImage,
                                             int cornerRadius) {

        m_size = size;
        m_color = color;
        m_hoverColor = hoverColor;
        if (text != nullptr) {
            m_pText = text;
            m_bIsTextSet = true;
            m_textColor = text->getTextColor();
            m_textHoverColor = text->getTextHoverColor();

        }

        if (image != nullptr) {
            m_pImage = image;
            m_bIsImageSet = true;

        }
        m_textOffset = textOffset;
        m_imageOffset = imageOffset;
        m_iBorderWidth = borderWidth;
        m_borderColor = borderColor;
        m_bCenterText = centerText;
        m_bCenterImage = centerImage;
        m_iCornerRadius = cornerRadius;
        m_pMainWindow = MemoryManager::getInstance()->getMainWindow();
    }


    void ImprovedUsualButton::centralizeText() {
        sf::Vector2f pos = getPosition();

        if (!m_bCenterText)
            m_pText->setPosition({pos.x + m_textOffset.x, pos.y + m_textOffset.y});
        else {
            sf::Vector2f textSize = m_pText->getFullSize();

            m_pText->setPosition(
                    {pos.x + m_textOffset.x + m_size.x / 2 - textSize.x / 2,
                     pos.y + m_textOffset.y + m_size.y / 2 - textSize.y / 2});
        }
    }


    void ImprovedUsualButton::centralizeImage() {
        sf::Vector2f pos = getPosition();

        if (!m_bCenterImage)
            m_pImage->setPosition({pos.x + m_imageOffset.x, pos.y + m_imageOffset.y});
        else {
            sf::Vector2f textSize = m_pImage->getSize();

            m_pImage->setPosition(
                    {pos.x + m_imageOffset.x + m_size.x / 2 - textSize.x / 2,
                     pos.y + m_imageOffset.y + m_size.y / 2 - textSize.y / 2});
        }
    }

    void ImprovedUsualButton::checkClick(sf::Event &event) {
        if (m_bIsDeactivated) {
            m_bIsClicked = false;
            return;
        }

        if (m_bIsHovered)
            if (event.type == sf::Event::MouseButtonPressed) {
                m_bIsClicked = true;
                return;
            }

        m_bIsClicked = false;
    }

    void ImprovedUsualButton::checkHover() {
        sf::Vector2f pos = getPosition();
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_pMainWindow);

        if (mousePos.x > pos.x && mousePos.x < pos.x + m_size.x)
            if (mousePos.y > pos.y && mousePos.y < pos.y + m_size.y) {
                m_bIsHovered = true;
                return;
            }

        m_bIsHovered = false;
    }

    void ImprovedUsualButton::initialize() {
        setType("button");

        sf::Vector2f pos = getPosition();

        m_mainRect.setSize(m_size);
        m_mainRect.setPosition(pos);

        if (!m_bIsDeactivated)
            m_mainRect.setFillColor(m_color);
        else
            m_mainRect.setFillColor(m_deactivatedColor);

        if (m_iCornerRadius > 0) {
            m_mainRect.setSize({m_size.x - m_iCornerRadius * 2, m_size.y});
            m_mainRect.setPosition({pos.x + m_iCornerRadius, pos.y});

            m_cornerCircle.setRadius(m_iCornerRadius);

            m_sideRect.setPosition({pos.x, pos.y + m_iCornerRadius});
            m_sideRect.setSize({m_size.x, m_size.y - m_iCornerRadius * 2});

            if (!m_bIsDeactivated) {
                m_cornerCircle.setFillColor(m_color);
                m_sideRect.setFillColor(m_color);
                m_sideRect.setFillColor(m_color);
            } else {
                m_cornerCircle.setFillColor(m_deactivatedColor);
                m_sideRect.setFillColor(m_deactivatedColor);
                m_sideRect.setFillColor(m_deactivatedColor);
            }
        }

        if (m_iBorderWidth > 0 && m_iCornerRadius == 0) {
            RectangleShapePtr topLine = std::make_shared<sf::RectangleShape>();
            topLine->setSize({m_size.x + m_iBorderWidth * 2, (float) m_iBorderWidth}); // right
            topLine->setPosition({pos.x - m_iBorderWidth, pos.y - m_iBorderWidth}); // right
            m_vcBorderLines.push_back(topLine); // right

            RectangleShapePtr downLine = std::make_shared<sf::RectangleShape>();
            downLine->setSize({m_size.x + m_iBorderWidth, (float) m_iBorderWidth});// right
            downLine->setPosition({pos.x, pos.y + m_size.y});// right
            m_vcBorderLines.push_back(downLine);// right

            RectangleShapePtr leftLine = std::make_shared<sf::RectangleShape>();
            leftLine->setSize({(float) m_iBorderWidth, m_size.y + m_iBorderWidth * 2}); // right
            leftLine->setPosition({pos.x - m_iBorderWidth, pos.y - m_iBorderWidth});  // right
            m_vcBorderLines.push_back(leftLine); // right

            RectangleShapePtr rightLine = std::make_shared<sf::RectangleShape>();
            rightLine->setSize({(float) m_iBorderWidth, m_size.y + m_iBorderWidth});// right
            rightLine->setPosition({pos.x + m_size.x, pos.y});// right
            m_vcBorderLines.push_back(rightLine);// right

        } else if (m_iBorderWidth > 0 && m_iCornerRadius > 0) {
            RectangleShapePtr topLine = std::make_shared<sf::RectangleShape>();
            topLine->setSize({m_size.x + m_iBorderWidth * 2 - m_iCornerRadius * 2, (float) m_iBorderWidth}); // right
            topLine->setPosition({pos.x - m_iBorderWidth + m_iCornerRadius, pos.y - m_iBorderWidth}); // right
            m_vcBorderLines.push_back(topLine); // right

            ArcShapePtr topLeftArcShape = std::make_shared<ArcShape>();
            topLeftArcShape->setCenterPosition(pos);
            topLeftArcShape->setStartAngle(180);
            topLeftArcShape->setEndAngle(270);
//            m_vcCornerArcs.push_back(topLeftArcShape);

            ArcShapePtr test = std::make_shared<ArcShape>();
            test->setRadius(m_iCornerRadius);
            test->setColor(m_borderColor);
            test->setWidth(m_iBorderWidth);
            test->setCenterPosition({100 + (float)m_iCornerRadius, 100 + (float)m_iCornerRadius});
            test->setStartAngle(180);
            test->setEndAngle(270);
            m_vcCornerArcs.push_back(test);

            RectangleShapePtr downLine = std::make_shared<sf::RectangleShape>();
            downLine->setSize({m_size.x + m_iBorderWidth * 2 - m_iCornerRadius * 2, (float) m_iBorderWidth});// right
            downLine->setPosition({pos.x + m_iCornerRadius - m_iBorderWidth, pos.y + m_size.y});// right
            m_vcBorderLines.push_back(downLine);// right



//            RectangleShapePtr leftLine = std::make_shared<sf::RectangleShape>();
//            leftLine->setSize({(float) m_iBorderWidth, m_size.y + m_iBorderWidth * 2}); // right
//            leftLine->setPosition({pos.x - m_iBorderWidth, pos.y - m_iBorderWidth});  // right
//            m_vcBorderLines.push_back(leftLine); // right
//
//            RectangleShapePtr rightLine = std::make_shared<sf::RectangleShape>();
//            rightLine->setSize({(float) m_iBorderWidth, m_size.y + m_iBorderWidth});// right
//            rightLine->setPosition({pos.x + m_size.x, pos.y});// right
//            m_vcBorderLines.push_back(rightLine);// right

            for (auto &arcShape: m_vcCornerArcs) {

                arcShape->init();
                arcShape->initialize();


            }
//
        }


        if (m_bIsTextSet) {
            centralizeText();
            m_pText->initialize();

        }

        if (m_bIsImageSet) {
            centralizeImage();
            m_pImage->initialize();
        }


    }

    void ImprovedUsualButton::drawBorder(sf::RenderTarget &rt) {
        if (m_iBorderWidth > 0) {
            sf::Vector2f pos = getPosition();
            for (auto &borderLine: m_vcBorderLines) {
                rt.draw(*borderLine);
            }
            for (auto &cornerArc: m_vcCornerArcs) {
                cornerArc->draw(rt);
            }

        }


    }

    void ImprovedUsualButton::setSize(const sf::Vector2f &size) {
        m_size = size;
        initialize();
    }

    void ImprovedUsualButton::setSize(float w, float h) {
        m_size.x = w;
        m_size.y = h;
        initialize();
    }


    void ImprovedUsualButton::setTextOffset(const sf::Vector2f &offset) {
        m_textOffset = offset;
        initialize();
    }

    void ImprovedUsualButton::setImageOffset(const sf::Vector2f &offset) {
        m_imageOffset = offset;
        initialize();
    }


    void ImprovedUsualButton::setBorderWidth(int width) {
        m_iBorderWidth = width;
        initialize();
    }

    void ImprovedUsualButton::setCornerRadius(int radius) {
        m_iCornerRadius = radius;
        initialize();
    }


    void ImprovedUsualButton::setText(const TextPtr &text) {
        m_pText = text;
        m_textColor = text->getTextColor();
        m_textHoverColor = text->getTextHoverColor();
        m_bIsTextSet = true;
        initialize();
    }


    void ImprovedUsualButton::setImage(const ImagePtr &image) {
        m_pImage = image;
        m_bIsImageSet = true;
        initialize();
    }


    void ImprovedUsualButton::setBorderColor(const sf::Color &color) {
        m_borderColor = color;
        initialize();
    }

    void ImprovedUsualButton::setHoverColor(const sf::Color &color) {
        m_hoverColor = color;
        initialize();
    }

    void ImprovedUsualButton::setCenteringText(bool center) {
        m_bCenterText = center;
        initialize();
    }

    void ImprovedUsualButton::setCenteringImage(bool center) {
        m_bCenterImage = center;
        initialize();
    }


    void ImprovedUsualButton::setColor(const sf::Color &color) {
        m_color = color;
        initialize();
    }

    void ImprovedUsualButton::setDeactivatedColor(const sf::Color &color) {
        m_deactivatedColor = color;
        initialize();
    }

    void ImprovedUsualButton::setStyle(ButtonStyle &buttonStyle) {
        m_size = buttonStyle.getSize();
        m_iBorderWidth = buttonStyle.getBorderWidth();
        m_iCornerRadius = buttonStyle.getCornerRadius();
        m_color = buttonStyle.getColor();
        m_borderColor = buttonStyle.getBorderColor();
        m_bIsDeactivated = buttonStyle.isDeactivated();
        m_textOffset = buttonStyle.getTextOffset();
        m_imageOffset = buttonStyle.getImageOffset();
        m_hoverColor = buttonStyle.getHoverColor();
        m_deactivatedColor = buttonStyle.getDeactivatedColor();
        m_bCenterText = buttonStyle.centerText();
        m_bCenterImage = buttonStyle.centerImage();
        initialize();
    }


    bool ImprovedUsualButton::isHovered() const {
        return m_bIsHovered;
    }

    bool ImprovedUsualButton::isClicked() {
        bool buff = m_bIsClicked;
        m_bIsClicked = false;
        return buff;
    }

    sf::Vector2f ImprovedUsualButton::getSize() {
        return m_size;
    }


    void ImprovedUsualButton::activate() {
        if (!m_bIsDeactivated) return;
        m_bIsDeactivated = false;
        initialize();
    }

    void ImprovedUsualButton::deactivate() {
        if (m_bIsDeactivated) return;
        m_bIsDeactivated = true;
        initialize();
    }


    void ImprovedUsualButton::draw(sf::RenderTarget &rt) {
        drawBorder(rt);

        rt.draw(m_mainRect);

        if (m_iCornerRadius > 0) {
            sf::Vector2f pos = getPosition();

            m_cornerCircle.setPosition({pos.x, pos.y});
            rt.draw(m_cornerCircle);

            m_cornerCircle.setPosition({pos.x + m_size.x - m_iCornerRadius * 2, pos.y});
            rt.draw(m_cornerCircle);

            m_cornerCircle.setPosition({pos.x, pos.y + m_size.y - m_iCornerRadius * 2});
            rt.draw(m_cornerCircle);

            m_cornerCircle.setPosition(
                    {pos.x + m_size.x - m_iCornerRadius * 2, pos.y + m_size.y - m_iCornerRadius * 2});
            rt.draw(m_cornerCircle);


            rt.draw(m_sideRect);

        }

        if (m_bIsTextSet) {
            m_pText->draw(rt);
        }

        if (m_bIsImageSet) {
            m_pImage->draw(rt);
        }


    }

    void ImprovedUsualButton::handleSFMLEvent(sf::Event &event) {
        checkClick(event);
    }

    void ImprovedUsualButton::update() {
        checkHover();

        if (!m_bIsDeactivated) {

            if (m_bIsHovered) {

                if (!m_bJustHovered) {
                    if (m_bIsTextSet)
                        m_pText->setTextColor(m_textHoverColor);

                    m_mainRect.setFillColor(m_hoverColor);

                    if (m_iCornerRadius > 0) {
                        m_cornerCircle.setFillColor(m_hoverColor);
                        m_sideRect.setFillColor(m_hoverColor);

                    }

                    m_bJustHovered = true;
                }
            } else {
                if (m_bJustHovered) {


                    if (m_bIsTextSet)
                        m_pText->setTextColor(m_textColor);

                    m_mainRect.setFillColor(m_color);

                    if (m_iCornerRadius > 0) {
                        m_cornerCircle.setFillColor(m_color);
                        m_sideRect.setFillColor(m_color);
                    }
                    m_bJustHovered = false;
                }

            }
        }
    }

}