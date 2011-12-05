#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "MoveData.h"
#include "Player.h"
#include "Cell.h"

using namespace std;

class Board;
class MoveData;

class GamePiece: public sf::Sprite
{

    public:

        enum {
            Pawn,
            Rook,
            Bishop,
            Queen,
            Knight,
            King,

            STATE_IDLE,   //Piece is ready to use
            STATE_TURN,//Piece is reset to default.
            STATE_SLEEP,   //Ready to be activated.
            STATE_DEAD, //Has been taken out of the game (can wake() still)
        };

        struct Exception {
            const int Path      =   0;
        };

        GamePiece();
        ~GamePiece();


        bool Move(MoveData MoveData);

        /********************************************************************\
                "Remember a valid path that has been found. Store in PossibleMoves"
            NAME:       RememberPath()
            RETRUNS:     bool


        /*******************************************************************/
        bool RememberPath(MoveData& MoveData);

        void showPossibleMovesOnBoard();
        void hidePossibleMovesOnBoard();

        void setGridPos(sf::Vector2i coord);
        void setType(int nType);
        void setOwner(Player* pl);
        void click();
        Player* Owner();
        void setOwner(int pl);
        int getType();

        int GetState();
        void SetState(int state);

        void startTurn();
        void endTurn();

        void think();

        void wake();
        void turn();
        void sleep();

        void kill();
        bool isAlive();
        bool isIdle();

        bool isAwake();

        vector<MoveData> FindPossibleMoves(sf::Vector2i from);

        //This is a list of possible moves that this piece can make on a turn.
        //The move vector contains the starting cell, the ending cell, and an Instance of MoveData
        vector<MoveData> PossibleMoves;

        bool hasMoved;
        int index;
        bool selected;
        int owner;

    protected:
    private:

        void FindPossibleMoves();
        void FindPossibleMoves(sf::Vector2i from, vector<MoveData>& storage);

        void incrementCoord(int* x, int* y, int dirX, int dirY);
        void _setImage(const std::string& fname);

        sf::Image Image;

        int m_state;
        int type;
        Cell currentCell;
        int moveOrientation; //+1 for down movement -1 for up movement
};

#endif // GAMEPIECE_H
