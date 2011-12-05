#include "Board.h"
#include "GamePiece.h"
#include "RenderHandler.h"
#include "Player.h"
#include "AI.h"

#include <string>

Board* Board::BoardPtr     =   NULL;

Board::Board() : TileMap(8, 60)
{
    m_isLoaded  =   false;
    setState(Board::STATE_NULL);
    m_activePlayer  =   NULL;
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

//    createCells();
    createPieces();

    m_isLoaded = true;

    return m_isLoaded;
}

bool Board::IsLoaded(){
    return m_isLoaded;
}


GamePiece Board::getGamePiece(int i) {
    return pieces[i];
}

int Board::ActivePlayer(){
    return m_activePlayer;
}

void Board::performAction(Cell& clickedCell){
    /*Cell&       c_selectedCell    =     cells[selectedCell.x][selectedCell.y];
    GamePiece&  selectedPiece     =     pieces[c_selectedCell.getPieceInCell()];

    if(!Player::Active()->ownsPiece(selectedPiece.index)){
        std::cout << "Active player (" << Player::Active()->id() << ") does not own this piece!";

        return;
    }

    std::cout << "\n**Generating MoveData based on click information...\n";

    //Organize out movement data
    MoveData MoveData(selectedPiece);
    MoveData.fromCell = sf::Vector2i(selectedCell.x, selectedCell.y);
    MoveData.toCell =   sf::Vector2i(clickedCell.getGridX(), clickedCell.getGridY());
    MoveData.outputDebugMessages = true;

    if(selectedPiece.Move(MoveData)){ //Attempt to move the piece
        m_actionPerformed = true;
    }else{
        std::cout << "MOVE IS NOT POSSIBLE\n";
    }*/
}

void Board::killPiece(int index){
    pieces[index].kill();
}

//Make attacking possible
//
bool Board::Click(sf::Vector2f mCoord){ //Event::Data e
    TileMap::Click(mCoord);

    //Now there may be cells selected.
    try{
        Cell clickedCell = GetSelection();

       // if()
    }

    catch(TMapException e){
        std::cout << e.why << std::endl;
    }
}

void Board::removePieceFromCell(sf::Vector2i cell){
    /*if(cells[cell.x][cell.y].occupied){
        int index   =   cells[cell.x][cell.y].getPieceInCell();

        cells[cell.x][cell.y].removePiece();

        //Move to somewhere evenyually..
        pieces[index].SetPosition(0, 0);
        pieces[index].setGridPos(9, 9);
    }*/
}

void Board::createPieces(){
    Rules rules;

    int numPawns    = rules.placement(GamePiece::Pawn);
    int numRooks    = rules.placement(GamePiece::Rook);
    int numKnights  = rules.placement(GamePiece::Knight);
    int numBishops  = rules.placement(GamePiece::Bishop);
    int total = 0;

    //Create Player 1 Pawns
    for(int p1PawnCount = 0; p1PawnCount<numPawns; p1PawnCount++){
        pieces[p1PawnCount].index = p1PawnCount;
        pieces[p1PawnCount].setType(GamePiece::Pawn);
        pieces[p1PawnCount].setOwner(1);
        pieces[p1PawnCount].setGridPos(sf::Vector2i(p1PawnCount, 6));
    }

    total += numPawns;

    //Create Player 2 Pawns
    for(int p2pawnCount = 0; p2pawnCount<numPawns; p2pawnCount++){
        int index = p2pawnCount+total;
        pieces[index].index = index;
        pieces[index].setType(GamePiece::Pawn);
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
        pieces[index].setType(GamePiece::Rook);
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
        pieces[index].setType(GamePiece::Rook);
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
        pieces[index].setType(GamePiece::Knight);
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
        pieces[index].setType(GamePiece::Knight);
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
        pieces[index].setType(GamePiece::Bishop);
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
        pieces[index].setType(GamePiece::Bishop);
        pieces[index].setOwner(2);
        pieces[index].setGridPos(sf::Vector2i(xPos, 0));
    }

    total += numBishops;

    //p1 queen
    pieces[total].index = total;
    pieces[total].setType(GamePiece::Queen);
    pieces[total].setOwner(1);
    pieces[total].setGridPos(sf::Vector2i(4, 7));

    total++;

    //p2 queen
    pieces[total].index = total;
    pieces[total].setType(GamePiece::Queen);
    pieces[total].setOwner(2);
    pieces[total].setGridPos(sf::Vector2i(4, 0)) ;

    total++;

    //p1 king
    pieces[total].index = total;
    pieces[total].setType(GamePiece::King);
    pieces[total].setOwner(1);
    pieces[total].setGridPos(sf::Vector2i(3, 7));

    total++;

    //p2 king
    pieces[total].index = total;
    pieces[total].setType(GamePiece::King);
    pieces[total].setOwner(2);
    pieces[total].setGridPos(sf::Vector2i(3, 0));

    for(int i=0; i<32;i++){
        RenderHandler::Get()->addComponent(pieces[i]);
    }
}

/*void Board::createCells(){
    cellSize    = 60;

    selectedCell.x = 9;
    selectedCell.y = 9;

    width = cellSize*8;
    height = cellSize*8;

    screenWidth = RenderHandler::Window()->GetWidth();
    screenHeight = RenderHandler::Window()->GetHeight();

    X = (screenWidth/2)-(width/2);
    Y = (screenHeight/2)-(height/2);

    //Set up cell array
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            cells[i][j].setGridPos(i, j);
            cells[i][j].setSize(cellSize, cellSize);
            cells[i][j].SetX(calculateCellPosX(i));
            cells[i][j].SetY(calculateCellPosY(j));
            cells[i][j].setToBoardColor();

            RenderHandler::Get()->addComponent(cells[i][j], 3);
        }
    }
}
*/
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
        std::cout << "INIT\n";
        BoardPtr = new Board();
    }

    return BoardPtr;
}

Board* Board::Get(){
    return Get(true);
}
/*
void Board::unload(){
    RenderHandler* RenderHandler = RenderHandler::Get();

    for(int pindex=0; pindex<32; pindex++){
        RenderHandler->removeComponent(&pieces[pindex]);
        pieces[pindex].~GamePiece();
    }

    for(int x=0; x<8; x++){
        for(int y=0; y<8; y++){
           RenderHandler->removeComponent(&cells[x][y]);
           cells[x][y].~Cell();
        }
    }
}*/

//End the current player's turn
void Board::turn(){
    deselect();

    if(m_activePlayer == NULL){
        m_activePlayer = 1;
    }else{
        if(m_activePlayer == 1){
            m_activePlayer = 2;
        }else{
            m_activePlayer = 1;
        }
    }

    setState(Board::STATE_TURN);

    std::cout << "Active player is " << m_activePlayer << ", Player::Active() returns " << Player::Active()->id() << std::endl;
}

void Board::think(){
    if(getState() == STATE_NULL || getState() == STATE_PAUSE) return;

    if(getState() == STATE_PLAY || getState() == STATE_TURN){
        for(int i=0;i<32;i++){
            if(pieces[i].isAlive() || pieces[i].isIdle()){
                pieces[i].think();
            }
        }
    }

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
                turn();
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
                deselect();
                m_actionPerformed = false;

                turn();
            }
            break;

        case STATE_TURN:
            setState(STATE_PLAY);
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

}

void Board::spacePressed(){
    m_actionPerformed = true;
}

void Board::highlightCell(int x, int y, bool moveType){
   // cells[x][y].highlightOn(moveType);
}

void Board::hideCellHighlight(int x, int y){
   // cells[x][y].highlightOff();
}

bool Board::cellIsInBounds(sf::Vector2i coord){
    if(coord.x < 0 || coord.x > 7 || coord.y < 0 || coord.y > 7){
        return false;
    }

    return true;
}
