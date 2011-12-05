#ifndef AIMOVE_H
#define AIMOVE_H

#include <vector>

#include "MoveData.h"

using namespace std;

/*****************************************
    This class characterizes an AI's move
*****************************************/
class MoveData;
class AIMove
{
    public:
        ///These are the flags assigned to the moves that the AI parses
        ///A move can have multiple flags, for example,  if the piece would move
        ///     They are set equal to their modifiers, IE how they will affect a move's priority
        enum MoveFlag{
            MOVE_STRATEGIC, ///This move would serve to strategically position a piece for future ATTACK/DEFENSE moves.
                                ///This move will take priority if no other pressing ATTACK/DEFENSE moves are possible

            MOVE_ATTACK,        ///This move would jump an enemy piece

            MOVE_DEFENSE,       ///This move would docourage an enemy piece from jumping a friendly piece, IE
                                ///     if the enemy piece were to jump the friendly piece, this piece would be
                                ///     be in position to attack it.

            MOVE_SUICIDE,       ///This move would move the piece in such a way that it could be jumped next turn
            MOVE_RETREAT,        ///This move removes the piece from danger
            MOVE_BREAK          ///This move would cause another piece to be left defenseless
        };

        void addFlag(MoveFlag flag);
        bool hasFlag(MoveFlag flag);
        void setFlags();


        AIMove(MoveData nmove);
        virtual ~AIMove();
    protected:
    private:
        vector<MoveFlag>flags;
        MoveData move;
};

#endif // AIMOVE_H
