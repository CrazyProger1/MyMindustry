//
// Created by crazy on 13.04.2022.
//

#ifndef MYMINDUSTRY_GRID_H
#define MYMINDUSTRY_GRID_H

#include "Button.h"
#include "Text.h"

namespace engine {
    class Grid {

    private:
        std::map<EntityPtr, sf::Vector2i> m_mpEntities;
        sf::Vector2f m_size;
        sf::Vector2f m_position;
        int m_iCols = 1, m_iRows = 1;
        bool m_bResizeButtons = true;
    public:
        void addEntity(const EntityPtr &entity, int column = 0, int row = 0);

        void setSize(const sf::Vector2f &size);

        void setPosition(const sf::Vector2f &position);

        void setCols(int cols);

        void setRows(int rows);

        void setResizeButtons(bool resize);

        void align(const str &pos = "tl"); // tl tr center dl dr
    };
}


#endif //MYMINDUSTRY_GRID_H
