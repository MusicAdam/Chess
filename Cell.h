#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell: public sf::Shape
{
    public:
        Cell();
        void setSize(int nSize);
        int getSize();
        void SetColor(sf::Color nColor);
        void create();
        void setToBoardColor();
        void setGridPos(int x, int y);
        int getGridX();
        int getGridY();
        void click();
        void putPieceInCell(int piece);
        int getPieceInCell();
        void removePieceFromCell();

        bool occupied;
        bool clicked;
        bool important; //Flags a cells as important (should be drawn last, so it is on top)
        sf::Color colorWhite;
        sf::Color colorBlack;
        sf::Color colorHighlight;
    protected:
    private:
        int size;
        int gridX;
        int gridY;
        int inCell;
        sf::Color color;
};

#endif // CELL_H
