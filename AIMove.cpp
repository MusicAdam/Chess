#include "AIMove.h"

AIMove::AIMove(MoveData nmove)
{
    //ctor
    move    =   nmove;

}

AIMove::~AIMove()
{
    //dtor
}

/*
///These are the flags assigned to the moves that the AI parses
        ///A move can have multiple flags
        enum {
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
*/
void AIMove::setFlags(){
    if(move.isAttackMove()){
        addFlag(MOVE_ATTACK);
    }else if(move.isDefaultMove()){
        //Check for defensive move

        //Check if piece would be able to jump friendly piece (as in, if the enemy piece were to jump the firendly piece, would this move allow the piece to jump back)
       //MoveData testMove(move.pieceType, move.pieceIndex);
    }
}

/*********************************************
    "Adds a movement flag"

    return  void
*******************************************/
void AIMove::addFlag(MoveFlag flag){
    flags.push_back(flag);
}

/*********************************************
    "Check if we have a flag"

    return  bool
*******************************************/
bool AIMove::hasFlag(MoveFlag flag){
    vector<MoveFlag>::iterator it;

    for(it=flags.begin(); it<flags.end(); it++){
        if((*it) == flag){
            return true;
        }
    }

    return false;
}
