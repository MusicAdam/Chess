#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include "GUI/Component.h"

class Cell: public Component
{
    public:
        Cell();
        ~Cell();
        void SetColor(sf::Color nColor);
        void setToBoardColor();
        void setGridPos(int x, int y);
        void setGridPos(sf::Vector2i coord);
        int getGridX();
        int getGridY();
        sf::Vector2i getGridPos();
        void click();
        void putPieceInCell(int piece);
        int getPieceInCell();
        void removePiece();

        void highlightOff();
        void highlightOn(bool attackMove);

        void outline(bool on);

        sf::Vector2f GetCenter();

        bool occupied;
        bool clicked;
        sf::Color colorWhite_h;
        sf::Color colorWhite_hr;
        sf::Color colorWhite;
        sf::Color colorBlack_h;
        sf::Color colorBlack_hr;
        sf::Color colorBlack;
        sf::Color colorHighlight;

        bool m_isHighlighted;
        int size;
        sf::Vector2i gridPos;
    protected:
    private:
        int inCell;
        sf::Color color;
};

#endif // CELL_H
