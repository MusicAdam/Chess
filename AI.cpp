#include "AI.h"
#include "Board.h"
#include "GamePiece.h"
#include "MoveData.h"
#include "AIMove.h"

AI* AI::aiPtr = NULL;

AI::AI()
{
    dontMove = false;
    //Sets to initial state
    clean();
}

AI::~AI()
{
    //dtor
}


static AI* AI::Get(){
    if(aiPtr == NULL){
        aiPtr = new AI();
    }

    return aiPtr;
}

static void AI::clean(){
    aiPtr = NULL;
}

//Waits for user input
void AI::dbg_wait(){
    //char* whocares;
    //std::cin;
}

static void AI::GetMove(){

    AI* ai = Get();
    //int = piece index
    //MoveList = piece's move list


    //Get all moves
    for(int index=0; index<32; index++){
        if(!Board::Get()->getGamePiece(index).isAwake()){
            Board::Get()->getGamePiece(index).wake();
        }

        if(Player::Active()->ownsPiece(index)){
            ai->FriendlyMoves.push_back(Board::Get()->getGamePiece(index).PossibleMoves);
        }else{
            ai->EnemyMoves.push_back(Board::Get()->getGamePiece(index).PossibleMoves);
        }
    }


    //Store single moves by their priority
    //int = priority
    //MoveData = the move
    multimap<int, AIMove> SortedMoves;


    int pieceIndex;
    MoveData pieceMoveData;
    vector<MoveData>::iterator PieceMoves_it;
    int counter = 0;

    for(ai->Move_it = ai->FriendlyMoves.begin(); ai->Move_it != ai->FriendlyMoves.end(); ++ai->Move_it){
        for(PieceMoves_it=(*ai->Move_it).begin(); PieceMoves_it < (*ai->Move_it).end(); PieceMoves_it++){
            pieceMoveData = (*PieceMoves_it);

            //Create a new AIMove possiblility
            AIMove newMove(pieceMoveData);
        }
    }

    Get()->dontMove = true;

}

