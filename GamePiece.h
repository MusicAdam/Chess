#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "MoveData.h"
#include "Cell.h"

class Board;

namespace Exception{
    const int Fatal     =   0;
    const int Path      =   1;
}

class GamePiece: public sf::Sprite
{

    public:
        enum {
            Pawn,
            Rook,
            Bishop,
            Queen,
            Knight,
            King
        };

        GamePiece();

        /*
            Attempts to move the piece to another cell.


        */
        bool canMove(Board& Board, Cell& toCell, int moveType);
        void setGridPos(int x, int y);
        int getGridX();
        int getGridY();
        void setType(int nType);
        void setOwner(int player);
        void click();
        int getOwner();
        int getType();
        bool hasMoved;
        int index;
        bool selected;
    protected:
    private:
        void incrementCoord(int* x, int* y, int dirX, int dirY);

        int type;
        int gridX;
        int gridY;
        int owner;
        int moveOrientation; //+1 for down movement -1 for up movement
};

#endif // GAMEPIECE_H
