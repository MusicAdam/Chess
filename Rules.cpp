#include "Rules.h"

Rules::Rules()
{

}

int Rules::placement(int type){
    switch(type){
        case GamePiece::Pawn:
            return 8;
        case GamePiece::King:
            return 1;
        case GamePiece::Rook:
            return 2;
        case GamePiece::Bishop:
            return 2;
        case GamePiece::Queen:
            return 1;
        case GamePiece::Knight:
            return 2;
    }
}
