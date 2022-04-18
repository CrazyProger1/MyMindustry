//
// Created by crazy on 15.04.2022.
//

#ifndef MYMINDUSTRY_ARCSHAPE_H
#define MYMINDUSTRY_ARCSHAPE_H

#include <memory>
#include <iostream>
#include "../Entity.h"
#include <cmath>

namespace engine {
    typedef std::shared_ptr<sf::CircleShape> CircleShapePtr;

    class ArcShape : public engine::Entity {
    private:
        float m_fltWidth = 2;
        float m_fltRadius = 100;
        int m_iStartAngle = 1;
        int m_iEndAngle = 90;
        sf::Vector2f m_centerPosition = {100, 100};
        sf::Vertex *m_pVertexArray{};
        sf::Color m_color = {255, 0, 0};
        std::vector<CircleShapePtr> m_vcArcParts;

    public:

        explicit ArcShape(float width = 1, float radius = 10, int startAngle = 1, int endAngle = 90,
                          const sf::Vector2f &centerPosition = {100, 100},
                          const sf::Color &color = {255, 0, 0});

        void setWidth(float width);

        void setRadius(float radius);

        void setStartAngle(int angle);

        void setEndAngle(int angle);

        void setCenterPosition(const sf::Vector2f &position);

        void setColor(const sf::Color &color);

        void initialize() override;

        void draw(sf::RenderTarget &rt) override;
    };

    typedef std::shared_ptr<ArcShape> ArcShapePtr;

}


#endif //MYMINDUSTRY_ARCSHAPE_H
