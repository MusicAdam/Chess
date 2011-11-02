#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <SFML/Graphics.hpp>
#include "GamePiece.h"

class MoveData
{
    public:

        enum {
            Forward              = 0,    //Only forward movement
            Perpendicular       = 2,    //restrict movement perpendicularl2
            Diagonal            = 3,   //Restrict movement diagonally
            All                 = 4    //Allow movement in all directions
        };


        MoveData(int pieceType);

        int direction;  //First element = first action direction, second element = second action direction
        sf::Vector2i distance;    //First element = first action direction, second element = second action direction
        bool OnlyForward;    //Allows only forward movement
    protected:
    private:
};

#endif // MOVEDATA_H
