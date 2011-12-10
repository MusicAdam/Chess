#include "Board.h"
#include "Piece.h"
#include "RenderHandler.h"
#include "Player.h"
#include "AI.h"

#include <string>

Board* Board::BoardPtr     =   NULL;

Board::Board() : TileMap(8, 60)
{
    m_isLoaded  =   false;
    setState(Board::STATE_NULL);
    m_activePlayer  =   1;
    m_actionPerformed = false;
    m_selectedPiece = NULL;

    SetPosition((RenderHandler::Get()->Window()->GetWidth()/2)-(MapSize()/2), (RenderHandler::Get()->Window()->GetHeight()/2)-(MapSize()/2));
}

Board::~Board(){

}

//Loads the board
bool Board::load(){
    if(m_isLoaded) return true;

    TileMap::load();

//    createSquares();
    createPieces();

    m_isLoaded = true;

    return m_isLoaded;
}

bool Board::IsLoaded(){
    return m_isLoaded;
}


Piece* Board::GetPiece(int i) {
    return &pieces[i];
}

int Board::ActivePlayer(){
    return m_activePlayer;
}

void Board::Deselect(){
    TileMap::Deselect();

    m_selectedPiece = NULL;
}

void Board::DebugClick(sf::Vector2f mCoord){
    try{
        Square* clickedSquare = GetSquare(GetGridFromPixel(mCoord));

        std::cout << "********************************\n";
        std::cout << "************Click Data**********\n";
        std::cout << "Square:\t\t" << clickedSquare->gridPos.x << ", " << clickedSquare->gridPos.y << std::endl;
        if(clickedSquare->Occupied()){
            std::cout << "Square points to:\t" << clickedSquare->GetPiece()->index << std::endl;
        }else{
            std::cout << "Square points to:\tNULL\n";
        }

        if(GetPiece(clickedSquare->GetPiece()->index)->GetSquare() == NULL){
            std::cout << "Piece points to square:\tNULL\n";
        }else{
            Square* sq = GetPiece(clickedSquare->GetPiece()->index)->GetSquare();
            std::cout << "Piece in square:\t" << clickedSquare->GetPiece()->index << std::endl;
            std::cout << "Piece points to square:\t" << sq->gridPos.x << ", " << sq->gridPos.y << std::endl;
        }
    }
    catch(ChessException e){
        std::cout << e.why << "\n";
    }
    catch(TMapException e){
        std::cout << e.why << "\n";
    }
}

void Board::DebugPreviousSelection(sf::Vector2f mCoord){
    std::cout << "********************************\n";
    std::cout << "************ Pointers **********\n";
    if(m_selectedPiece == NULL){
        std::cout << "m_selectedPiece = NULL\n";
    }else{
        std::cout << "m_selectedPiece = ("<< m_selectedPiece->GetPos().x << ", "<< m_selectedPiece->GetPos().y <<")\n";
    }
}

void Board::performAction(Square* clickedSquare){
    if(!Player::Active()->OwnsPiece(m_selectedPiece->index)){
        std::cout << "Active player (" << Player::Active()->id() << ") does not own this piece!";

        return;
    }

    /*** GENERATING MOVE DATA **/
    MoveData MoveData(*m_selectedPiece);
    MoveData.fromSquare = sf::Vector2i(m_selectedPiece->GetPos().x, m_selectedPiece->GetPos().y);
    MoveData.toSquare =   sf::Vector2i(clickedSquare->gridPos.x, clickedSquare->gridPos.y);
    MoveData.outputDebugMessages = true;

    if(m_selectedPiece->Move(MoveData)){ //Attempt to move the piece
        m_actionPerformed = true;
    }else{
        std::cout << "MOVE IS NOT POSSIBLE\n";
    }
}

//Make attacking possible
//
bool Board::Click(sf::Vector2f mCoord){ //Event::Data e
    //Now there may be Squares selected.
    bool canPerformAction = true;
    Square* selectedSquare = NULL;
    Square* clickedSquare  = NULL;

    try{
        selectedSquare  = GetSelection();
        clickedSquare   = GetSquare(GetGridFromPixel(mCoord));

        canPerformAction = true;
    }

    catch(TMapException e){
        std::cout << "Board::Click():> Cannot perform action: " << e.why << std::endl;
        canPerformAction = false;
    }

    if(canPerformAction){
        //Switch selection
        if(clickedSquare->Occupied() && Player::Active()->OwnsPiece(clickedSquare->GetPiece())){
            TileMap::Click(mCoord);
            m_selectedPiece = clickedSquare->GetPiece();
        }else{ //Perform action
            performAction(clickedSquare);
        }
    }else{
        //try to make a selection
        try{
            Square* clickedSquare = GetSquare(GetGridFromPixel(mCoord));

            if(clickedSquare->Occupied()){
                if(Player::Active()->OwnsPiece(clickedSquare->GetPiece())){
                    TileMap::Click(mCoord);

                    m_selectedPiece = clickedSquare->GetPiece();
                }else{
                    std::cout << "Board::Click():> Cannot select square: This piece does not belong to you!" << std::endl;
                }
            }else{
                std::cout << "Board::Click():> Cannot select square: This square has no piece in it!" << std::endl;
            }
        }

        catch(TMapException e){
            std::cout << "Board::Click():> Cannot select square: " << e.why << std::endl;
        }
    }


}

void Board::createPieces(){
    int numPawns    = 8;
    int numRooks    = 2;
    int numKnights  = 2;
    int numBishops  = 2;
    int total = 0;

    //Create Player 1 Pawns
    for(int p1PawnCount = 0; p1PawnCount<numPawns; p1PawnCount++){
        pieces[p1PawnCount].index = p1PawnCount;
        pieces[p1PawnCount].setType(Piece::Pawn);
        pieces[p1PawnCount].setOwner(1);
        pieces[p1PawnCount].setGridPos(sf::Vector2i(p1PawnCount, 6));
    }

    total += numPawns;

    //Create Player 2 Pawns
    for(int p2pawnCount = 0; p2pawnCount<numPawns; p2pawnCount++){
        int index = p2pawnCount+total;
        pieces[index].index = index;
        pieces[index].setType(Piece::Pawn);
        pieces[index].setOwner(2);
        pieces[index].setGridPos(sf::Vector2i(p2pawnCount, 1));
    }

    total += numPawns;

    //Create player 1 rooks
    for(int p1rookCount = 0; p1rookCount<numRooks; p1rookCount++){
        int index = p1rookCount + total;
        pieces[index].index = index;
        int xPos=0;

        if(p1rookCount == 1){
            xPos = 7;
        }
        pieces[index].setType(Piece::Rook);
        pieces[index].setOwner(1);
        pieces[index].setGridPos(sf::Vector2i(xPos, 7));
    }

   total += numRooks;

    //Create player 2 rooks
    for(int p2rookCount = 0; p2rookCount<numRooks; p2rookCount++){
        int index = p2rookCount + total;
        pieces[index].index = index;
        int xPos=0;

        if(p2rookCount == 1){
            xPos = 7;
        }
        pieces[index].setType(Piece::Rook);
        pieces[index].setOwner(2);
        pieces[index].setGridPos(sf::Vector2i(xPos, 0));


    }

    total += numRooks;

    //Create player 1 knights
    for(int p1knightCount = 0; p1knightCount<numKnights; p1knightCount++){
        int index = p1knightCount + total;
        pieces[index].index = index;
        int xPos=1;

        if(p1knightCount == 1){
            xPos = 6;
        }
        pieces[index].setType(Piece::Knight);
        pieces[index].setOwner(1);
        pieces[index].setGridPos(sf::Vector2i(xPos, 7));
    }

   total += numKnights;

    //Create player 2 knights
    for(int p2knightCount = 0; p2knightCount<numKnights; p2knightCount++){
        int index = p2knightCount + total;
        int xPos=1;
        pieces[index].index = index;

        if(p2knightCount == 1){
            xPos = 6;
        }
        pieces[index].setType(Piece::Knight);
        pieces[index].setOwner(2);
        pieces[index].setGridPos(sf::Vector2i(xPos, 0));
    }

    total += numKnights;

    //Create player 1 bishops
    for(int p1bishopCount = 0; p1bishopCount<numBishops; p1bishopCount++){
        int index = p1bishopCount + total;
        pieces[index].index = index;
        int xPos=2;

        if(p1bishopCount == 1){
            xPos = 5;
        }
        pieces[index].setType(Piece::Bishop);
        pieces[index].setOwner(1);
        pieces[index].setGridPos(sf::Vector2i(xPos, 7));
    }

   total += numBishops;

    //Create player 2 bishops
    for(int p2bishopCount = 0; p2bishopCount<numBishops; p2bishopCount++){
        int index = p2bishopCount + total;
        int xPos=2;

        if(p2bishopCount == 1){
            xPos = 5;
        }
        pieces[index].index = index;
        pieces[index].setType(Piece::Bishop);
        pieces[index].setOwner(2);
        pieces[index].setGridPos(sf::Vector2i(xPos, 0));
    }

    total += numBishops;

    //p1 queen
    pieces[total].index = total;
    pieces[total].setType(Piece::Queen);
    pieces[total].setOwner(1);
    pieces[total].setGridPos(sf::Vector2i(4, 7));

    total++;

    //p2 queen
    pieces[total].index = total;
    pieces[total].setType(Piece::Queen);
    pieces[total].setOwner(2);
    pieces[total].setGridPos(sf::Vector2i(4, 0)) ;

    total++;

    //p1 king
    pieces[total].index = total;
    pieces[total].setType(Piece::King);
    pieces[total].setOwner(1);
    pieces[total].setGridPos(sf::Vector2i(3, 7));

    total++;

    //p2 king
    pieces[total].index = total;
    pieces[total].setType(Piece::King);
    pieces[total].setOwner(2);
    pieces[total].setGridPos(sf::Vector2i(3, 0));

    for(int i=0; i<32;i++){
        RenderHandler::Get()->addComponent(pieces[i]);
    }
}

void Board::setState(const int nstate){
    m_state =   nstate;
    switch(nstate){
        case Board::STATE_NULL:
            std::cout << "============================== NULL ==============================\n";
            break;
        case Board::STATE_LOADING:
            std::cout << "============================== LOADING ==============================\n";
            break;
        case Board::STATE_EXIT:
            std::cout << "============================== EXIT ==============================\n";
            break;
        case Board::STATE_PLAY:
            std::cout << "============================== PLAY ==============================\n";
            break;
        case Board::STATE_PAUSE:
            std::cout << "============================== PAUSE ==============================\n";
            break;
        case Board::STATE_TURN:
            std::cout << "============================== TURN ==============================\n";
            break;
    }
}
const int Board::getState(){
    return m_state;
}

Board* Board::Get(bool init){
    if(BoardPtr == NULL && init){
        BoardPtr = new Board();
    }

    return BoardPtr;
}

Board* Board::Get(){
    return Get(true);
}

void Board::unload(){
    RenderHandler* RenderHandler = RenderHandler::Get();

    for(int pindex=0; pindex<32; pindex++){
        RenderHandler->removeComponent(&pieces[pindex]);
        pieces[pindex].~Piece();
    }

    TileMap::unload();
}

//End the current player's turn
void Board::turn(){
    Deselect();

    if(m_activePlayer == NULL){
        m_activePlayer = 1;
    }else{
        if(m_activePlayer == 1){
            m_activePlayer = 2;
        }else{
            m_activePlayer = 1;
        }
    }

    std::cout << "Active player is " << m_activePlayer << ", Player::Active() returns " << Player::Active()->id() << std::endl;
}

void Board::think(){
    if(getState() == STATE_NULL || getState() == STATE_PAUSE) return;

    //Board is loading.
    switch(getState())
    {
        case STATE_LOADING:
            /*if(m_isLoaded){
                turn();
                RenderHandler::Get()->invalidate();
            }else{
                load();
            }*/

            if(m_isLoaded && BoardPtr != NULL){
                setState(STATE_PLAY);
                RenderHandler::Get()->invalidate();
            }else{
                //construct (Lazy initialize) & load
                Board::Get()->load();
                m_isLoaded = true;
            }

            break;

        case STATE_PLAY:
            if(Player::Active()->isAI()){
                if(!AI::Get()->dontMove){
                    AI::GetMove();
                }
            }

            if(m_actionPerformed){
                Deselect();
                m_selectedPiece = NULL;
                m_actionPerformed = false;

                setState(STATE_TURN);
            }
            break;

        case STATE_TURN:
            try {
                turn();
                setState(STATE_PLAY);
            }

            catch(...){
                std::cout << "Unknown exception encountered, can not switch turn\n";
            }

            break;

        case STATE_EXIT:
            BoardPtr->unload();
            BoardPtr = NULL;

            Player::clean();
            AI::clean();

            //Tell player class to invalidate player information
            //Tell AI to invalidate

            RenderHandler::Get()->invalidate();
            break;

    }

    if(getState() == STATE_PLAY || getState() == STATE_TURN){
        for(int i=0;i<32;i++){
            if(pieces[i].isAlive() || pieces[i].isIdle()){
                pieces[i].think();
            }
        }
    }

}

void Board::spacePressed(){
    m_actionPerformed = true;
}

void Board::highlightSquare(int x, int y, bool moveType){
   // Squares[x][y].highlightOn(moveType);
}

void Board::hideSquareHighlight(int x, int y){
   // Squares[x][y].highlightOff();
}
