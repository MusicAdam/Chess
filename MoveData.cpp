#include "MoveData.h"

MoveData::MoveData(int pieceType)
{
    direction       =   All;
    distance.x      =   0;
    distance.y      =   0;

    switch(pieceType){
        case GamePiece::Pawn:
            direction       =   Forward;
            distance.y      =   1;
            break;
        case GamePiece::King:
            distance.x = 1;
            distance.y = 1;
            break;
        case GamePiece::Rook:
            direction       =   Perpendicular;
            distance.x      =   -1;
            distance.y      =   -1;
            break;
        case GamePiece::Bishop:
            direction       =   Diagonal;
            distance.x      =   -1;
            distance.y      =   -1;
            break;
        case GamePiece::Queen:
            direction       =   All;
            distance.x      =   -1;
            distance.y      =   -1;
            break;
        case GamePiece::Knight:
            direction       =   All;
            distance.y      =   2;
            distance.x      =   2;
            break;

    }
}
