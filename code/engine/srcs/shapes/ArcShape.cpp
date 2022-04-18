//
// Created by crazy on 15.04.2022.
//

#include "../../include/shapes/ArcShape.h"


namespace engine {
    ArcShape::ArcShape(float width, float radius, int startAngle, int endAngle, const sf::Vector2f &centerPosition,
                       const sf::Color &color) {
        m_fltWidth = width;
        m_fltRadius = radius;
        m_iStartAngle = startAngle;
        m_iEndAngle = endAngle;
        m_centerPosition = centerPosition;
        m_color = color;
    }

    void ArcShape::setWidth(float width) {
        m_fltWidth = width;
    }

    void ArcShape::setRadius(float radius) {
        m_fltRadius = radius;
    }

    void ArcShape::setStartAngle(int angle) {
        m_iStartAngle = angle;
    }

    void ArcShape::setEndAngle(int angle) {
        m_iEndAngle = angle;
    }

    void ArcShape::setCenterPosition(const sf::Vector2f &position) {
        m_centerPosition = position;
    }

    void ArcShape::setColor(const sf::Color &color) {
        m_color = color;
    }

    void ArcShape::initialize() {
        m_pVertexArray = new sf::Vertex[m_iEndAngle - m_iStartAngle];

        if (m_fltWidth == 1) {
            int i = 0;

            for (int angle = m_iStartAngle; angle < m_iEndAngle; ++angle) {


                float x, y;

                x = m_centerPosition.x + std::cos(angle * (M_PI / 180)) * m_fltRadius;
                y = m_centerPosition.y + std::sin(angle * (M_PI / 180)) * m_fltRadius;
                m_pVertexArray[i] = sf::Vertex({x, y}, m_color);
                i++;

            }
        } else {
            for (int angle = m_iStartAngle; angle < m_iEndAngle; ++angle) {
                CircleShapePtr arcPart = std::make_shared<sf::CircleShape>();

                float x, y;
                x = m_centerPosition.x + std::cos(angle * (M_PI / 180)) * m_fltRadius;
                y = m_centerPosition.y + std::sin(angle * (M_PI / 180)) * m_fltRadius;


                arcPart->setRadius(m_fltWidth / 2);

                arcPart->setFillColor(m_color);

                arcPart->setPosition(x, y);

                arcPart->setOrigin(m_fltWidth / 2, m_fltWidth / 2);

                m_vcArcParts.push_back(arcPart);
            }
        }
    }

    void ArcShape::draw(sf::RenderTarget &rt) {
        {
            if (m_fltWidth == 1) {
                rt.draw(m_pVertexArray, m_iEndAngle - m_iStartAngle, sf::Points);
            } else {
                for (auto &circleShape: m_vcArcParts) {
                    rt.draw(*circleShape);
                }
            }
        }
    }


}