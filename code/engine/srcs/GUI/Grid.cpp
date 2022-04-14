//
// Created by crazy on 13.04.2022.
//

#include "../../include/GUI/Grid.h"


namespace engine {

    void Grid::addEntity(const EntityPtr &entity, int row, int column) {
        m_mpEntities[entity] = {row, column};
    }

    void Grid::setSize(const sf::Vector2f &size) {
        m_size = size;
    }

    void Grid::setPosition(const sf::Vector2f &position) {
        m_position = position;
    }


    void Grid::setCols(int cols) {
        m_iCols = cols;
    }

    void Grid::setRows(int rows) {
        m_iRows = rows;
    }

    void Grid::setResizeButtons(bool resize) {
        m_bResizeButtons = resize;
    }


    void Grid::align(const str &pos) {
        float width = m_size.x / m_iCols;
        float height = m_size.y / m_iRows;

        for (auto &entityData: m_mpEntities) {

            EntityPtr entity = entityData.first;

            if (entity->getType() == "button") {
                if (m_bResizeButtons) {
                    entity->setSize(width, height);
                }
                sf::Vector2f entitySize = entity->getSize();
                if (pos == "tl") {
                    entity->setPosition(m_position.x + entityData.second.x * width,
                                        m_position.y + entityData.second.y * height);
                } else if (pos == "tr") {
                    entity->setPosition(m_position.x + entityData.second.x * width + width - entitySize.x,
                                        m_position.y + entityData.second.y * height);
                } else if (pos == "dl") {
                    entity->setPosition(m_position.x + entityData.second.x * width,
                                        m_position.y + entityData.second.y * height + height - entitySize.y);

                } else if (pos == "dr") {
                    entity->setPosition(m_position.x + entityData.second.x * width + width - entitySize.x,
                                        m_position.y + entityData.second.y * height + height - entitySize.y);
                } else if (pos == "center") {
                    entity->setPosition(m_position.x + entityData.second.x * width + (width - entitySize.x) / 2,
                                        m_position.y + entityData.second.y * height + (height - entitySize.y) / 2);
                }

            }
        }
    }


}