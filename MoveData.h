#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

class Cell;
class GamePiece;

//TODO: Move checkPath (rename to FindPath) to the board class. This class should not deal with cell data.

class MoveData
{
    public:

        enum {
            //Types of movement
            Perpendicular       =   1,    //restrict movement perpendicularly
            Diagonal            =   2,   //Restrict movement diagonally
            Knight              =   3,  //Knight movement
            IMPOSSIBLE          =   4,  //When the movement requested is not possible by any defined type of movement

            ATTACK              =  5,
            DEFAULT             =  6,

            //Used for the path finder
            COLLISION_FRIENDLY  =   7,  //We have collieded with a friendly piece
            COLLISION_ENEMY     =   8,  //We have collided with an enemy piece, triggers an attack move
            COLLISION_NONE      =   9,  //No collision detected

            NIL                 =   -10//Because NULL sucks sometimes
        };


        MoveData(GamePiece& Piece);
        MoveData();
        MoveData(int ptype, int pindex);

        bool isValid();
        void validate();

        void addFlag(int flag);
        void removeFlag(int flag);
        bool hasFlag(int flag);
        bool isAttackMove();
        bool isDefaultMove();
        void setMoveType(int type);

        bool isPossible();

        bool operator==(MoveData checkAgainst);

        int forward;    //Which direction is forward
        int pieceIndex, pieceType;
        int m_type;
        int collision_model;
        bool outputDebugMessages;
        bool ignoreCollisions;  //false by default, when true friendly collisions are ignored
        bool onlyForward;       //false by default, when true the piece can only move/jump forward
        int direction;  //The direction of the movement
        sf::Vector2i distance;  //x, y distance being moved
        sf::Vector2i range;     //total x, y distance that can be moved
        sf::Vector2i orientation; //x & y orientation

        sf::Vector2i fromCell;
        sf::Vector2i toCell;
    private:
        void _orient();
        void _distance();
        void _direction();

        bool checkPath(); //Check that a path between the two cells is possible
        bool checkRange();


        ///Movement Flags
            /**
                Movement flags define how a piece can move
            **/
        vector<int> flags;
};

#endif // MOVEDATA_H
