#include "MoveData.h"
#include "GamePiece.h"
#include "Cell.h"
#include "GamePiece.h"
#include "Board.h"
#include <string>

MoveData::MoveData(){}
MoveData::MoveData(GamePiece& Piece)
{
    pieceType       =   Piece.getType();
    pieceIndex      =   Piece.index;

    //Init defaults
    setMoveType(DEFAULT); //Default to non-attack move
    range.x      =   0;
    range.y      =   0;

    onlyForward         = false;
    ignoreCollisions    =   false;

    forward         = Piece.Owner()->forward();  //Which direction is forward
    orientation     = sf::Vector2i(NIL, NIL);

    fromCell        = sf::Vector2i(NIL, NIL);
    toCell          = sf::Vector2i(NIL, NIL);

    distance        = sf::Vector2i(-1, -1);
    direction       = NIL;

    outputDebugMessages = false;
    switch(pieceType){
        case GamePiece::Pawn:
            addFlag(Perpendicular);
            onlyForward = true;
            range.y      =   1;
            break;
        case GamePiece::King:
            addFlag(Diagonal);
            addFlag(Perpendicular);
            range.x = 1;
            range.y = 1;
            break;
        case GamePiece::Rook:
            addFlag(Perpendicular);
            range.x      =   -1;
            range.y      =   -1;
            break;
        case GamePiece::Bishop:
            addFlag(Diagonal);
            range.x      =   -1;
            range.y      =   -1;
            break;
        case GamePiece::Queen:
            addFlag(Diagonal);
            addFlag(Perpendicular);
            range.x      =   -1;
            range.y      =   -1;
            break;
        case GamePiece::Knight:
            addFlag(Knight);
            ignoreCollisions = true;
            range.y      =   2;
            range.x      =   2;
            break;

    }
}


/*********************************************
    "Sets the move type ATTACK or DEFAULT"

    return  void
*******************************************/
void MoveData::setMoveType(int type){
    m_type = type;

    if(isAttackMove()){
        if(pieceType == GamePiece::Pawn){
            flags.clear();
            addFlag(Diagonal);

            range.x = 1;
            range.y = 1;
        }
    }else if(isDefaultMove()){
        if(pieceType == GamePiece::Pawn){
            flags.clear();
            addFlag(Perpendicular);
            range.x = 0;
            range.y = 1;
        }
    }
}

/*********************************************
    "Check if move is DEFAULT"

    return bool
*******************************************/
bool MoveData::isDefaultMove(){
    return (m_type == DEFAULT) ? true : false;
}

/*********************************************
    "Check if move is ATTACK"

    return bool
*******************************************/
bool MoveData::isAttackMove(){
    return (m_type == ATTACK) ? true : false;
}

/*********************************************
    "Adds a movement flag"

    return  void
*******************************************/
void MoveData::addFlag(int flag){
    flags.push_back(flag);
}


/*********************************************
    "Remove a movement flag"

    return  void

    THIS DOESN'T WORK FOR SOME REASON
*******************************************/
void MoveData::removeFlag(int flag){
    vector<int>::iterator it;

    for(it=flags.begin(); it<flags.end(); it++){
        if((*it) == flag){
            flags.erase(it);
        }
    }
}

/*********************************************
    "Check if we have a flag"

    return  bool
*******************************************/
bool MoveData::hasFlag(int flag){
    vector<int>::iterator it;

    for(it=flags.begin(); it<flags.end(); it++){
        if((*it) == flag){
            return true;
        }
    }

    return false;
}

/*********************************************
    "Record which direction movement is
        taking place on each axis"

    return void;
*******************************************/
void MoveData::_orient(){
    if(toCell.x != NIL && fromCell.x != NIL){

        orientation.x = ((toCell.x - fromCell.x) < 0) ? -1 : 1;
        orientation.y = ((toCell.y - fromCell.y) < 0) ? -1 : 1;

    }
}

/*********************************************
    "Set the direction of movement"

    return void;
*******************************************/
void MoveData::_direction(){
    if(toCell.x == NIL || fromCell.x == NIL || orientation.x == NIL || distance.x == -1) return;

    if(distance.x == distance.y){
        direction = Diagonal;
    }else if((distance.x != 0 && distance.y == 0) || (distance.y != 0 && distance.x == 0)){
        direction = Perpendicular;
    }else{
        //Check for knight movement
        if(((distance.x == 2) && (distance.y == 1)) || ((distance.x == 1) && (distance.y == 2))){
            direction = Knight;
        }else{
            direction = IMPOSSIBLE;
        }
    }

}

/*********************************************
    "Check to see if all the required data
        is set."

    return  TRUE is all data is set
            FALSE if any data is NULL
*******************************************/
bool MoveData::isValid(){
    if(orientation.x == NIL || toCell.x == NIL || fromCell.x == NIL || distance.x == -1 || direction == NIL){
        return false;
    }

    return true;
}

/*********************************************
    "Attempt to orient() and distance()."

    return  void
*******************************************/
void MoveData::validate(){
    if(isValid()) return;

    if(toCell.x == NIL) return;
    if(!Board::Get()->cellIsInBounds(toCell)) return;

    _orient();
    _distance();
    _direction();

    if(Board::Get()->getCell(toCell.x, toCell.y).occupied){
        if(!Player::Active()->ownsPiece(Board::Get()->getCell(toCell.x, toCell.y).getPieceInCell())){
            setMoveType(ATTACK);
        }
    }
}

/*********************************************
    "Record the distance between two cells"

    return void;
*******************************************/
void MoveData::_distance(){
    if(toCell.x == NIL || fromCell.x == NIL) return;
    if(orientation.x == NIL) return;

    distance.x = (toCell.x - fromCell.x)*orientation.x;
    distance.y = (toCell.y - fromCell.y)*orientation.y;
}

/*******************************************************
    "Check if a move with the given data is possible"

    returns     TRUE if that move is possible.
                FALSE if the move is impossible.

    This function basically applies the MoveData to see
    if the move requested is possible by this piece.
*******************************************************/
bool MoveData::isPossible(){
    validate();

    if(!isValid()){
        if(outputDebugMessages) { std::cout << "Can not move piece " << pieceIndex << " (Type: " << pieceType << ") move from (" << fromCell.x << ", " << fromCell.y << ") to (" << toCell.x << ", " << toCell.y << ").\n\tMove data is not complete\n"; }

        return false; }

    if(direction == IMPOSSIBLE) {
        if(outputDebugMessages) { std::cout << "Can not move piece " << pieceIndex << " (Type: " << pieceType << ") move from (" << fromCell.x << ", " << fromCell.y << ") to (" << toCell.x << ", " << toCell.y << ").\n\tMove impossible.\n"; }
        return false;}

    if(hasFlag(direction)){
        if(onlyForward){
            if(orientation.y != forward){
                if(outputDebugMessages) { std::cout << "Can not move piece\n\tPiece can only move forward!\n"; }
                return false;
            }
        }

        if(checkRange()){
            return checkPath();
        }else{
            if(outputDebugMessages) { std::cout << "Can not move piece\n\tTarget is out of range\n"; }
        }
    }else{
        if(outputDebugMessages) { std::cout << "Can not move piece\n\tThis piece is not allowed to move in that direction (" << direction << ")!\n"; }
    }

    return false;
}


/***************************************************************
    "Checks to see if there are any obstructions in our path"

    return  TRUE if the path to this piece is clear
            FALSE if the path to this piece is not clear
**************************************************************/
bool MoveData::checkPath(){
    int collisionFlag = COLLISION_NONE;
    int checkX = fromCell.x;
    int checkY = fromCell.y;

    if(ignoreCollisions){
        if(Board::Get()->getCell(toCell.x, toCell.y).occupied){
            if(Player::Active()->ownsPiece(Board::Get()->getCell(toCell.x, toCell.y).getPieceInCell())){
                collisionFlag = COLLISION_FRIENDLY;
            }else{
                collisionFlag = COLLISION_ENEMY;
                checkX = toCell.x;
                checkY = toCell.y;
            }
        }
    }else{
        while(collisionFlag == COLLISION_NONE){
            if(direction == Diagonal){
                checkX += orientation.x;
                checkY += orientation.y;
            }else if(direction == Perpendicular){
                if(distance.x == 0){
                    checkY += orientation.y;
                }else{
                    checkX += orientation.x;
                }
            }

            Cell checkCell = Board::Get()->getCell(checkX, checkY);

            if(checkCell.occupied){
                if(Player::Active()->ownsPiece(checkCell.getPieceInCell())){
                    collisionFlag = COLLISION_FRIENDLY;
                }else{
                    collisionFlag = COLLISION_ENEMY;
                }
            }

            if(checkX == toCell.x && checkY == toCell.y){
                break;
            }
        }
    }

    collision_model = collisionFlag;

    if(collisionFlag == COLLISION_NONE){
        //std::cout << "No collision, path found\n";
        return true;
    }else{
        if(collisionFlag == COLLISION_FRIENDLY){
            //std::cout << "Friendly collision, path not found\n";
            return false;
        }else{
            if(checkX != toCell.x || checkY != toCell.y){
               // std::cout << "Enemy collision, path not found\n";
                return false;
            }else{
                return true;
            }
        }
    }
}

/*************************************************************
    "Checks to see if toCell is within our range"

    return  bool
**************************************************************/
bool MoveData::checkRange(){

    if(pieceType == GamePiece::Knight){
        if(((distance.x == 2) && (distance.y != 1)) || ((distance.x == 1) && (distance.y != 2))){
            if(outputDebugMessages) { std::cout << "Knight movement is out of range\n"; }
            return false;
        }
    }else{
        if(pieceType == GamePiece::Pawn){
            if(Board::Get()->getGamePiece(pieceIndex).hasMoved){
                range.y = 1;
            }else{
                range.y = 2;
            }
        }

        if(range.x != -1){
            if(distance.x > range.x){
                if(outputDebugMessages) { std::cout << "X movement is out of range\n"; }
                return false;
            }
        }

        if(range.y != -1){
            if(distance.y > range.y){
                if(outputDebugMessages) { std::cout << "Y movement is out of range\n"; }
                return false;
            }
        }
    }

    return true;
}

bool MoveData::operator==(MoveData checkAgainst){
    if(isValid() && checkAgainst.isValid()){
        if(fromCell == checkAgainst.fromCell && toCell == checkAgainst.toCell){
            return true;
        }
    }

    return false;
}


