#include "Board.h"
#include "GamePiece.h"

#include <string>

Board::Board(sf::RenderWindow &App, RenderHandler &RenderHandler)
{
    //Event::Data::callBack memPtr = Board::clickCell;

    //EventHandler.addListener(Event::MOUSE_RELEASE, memPtr);
    cellSize    = 60;

    selectedCell.x = 9;
    selectedCell.y = 9;

    width = cellSize*8;
    height = cellSize*8;

    screenWidth = App.GetWidth();
    screenHeight = App.GetHeight();

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

            RenderHandler.addComponent(cells[i][j], 3);
        }
    }

    createPieces();

    invalidate();
}

//Gets the cell position (origin, top left corner) relative to the window
float Board::calculateCellPosX(int gridX){
    return (gridX*cellSize)+X;
}

float Board::calculateCellPosY(int gridY){
    return (gridY*cellSize)+Y;
}

const sf::Vector2f Board::calculateCellPos(int gridX, int gridY){
    sf::Vector2f vector(calculateCellPosX(gridX), calculateCellPosY(gridY));

    return vector;
}

Cell Board::getCell(int i, int j) {
    return cells[i][j];
}

GamePiece Board::getGamePiece(int i) {
    return pieces[i];
}

int Board::getCellGridPosX(sf::RenderWindow &App, int mouseX, int mouseY){
    return (mouseX - ((App.GetWidth()/2)-(width/2)))/cellSize;
}

int Board::getCellGridPosY(sf::RenderWindow &App, int mouseX, int mouseY){
    return (mouseY - ((App.GetHeight()/2)-(height/2)))/cellSize;
}

const sf::Vector2f Board::getCellCenter(int cellX, int cellY){
    float posX = calculateCellPosX(cellX);
    float posY = calculateCellPosY(cellY);

    sf::Vector2f vector(posX+(cellSize/2), posY+(cellSize/2));

    return vector;
}

//If selected cell is set
bool Board::cellIsSelected(){
    if(selectedCell.x == 9 && selectedCell.y == 9){
        return false;
    }

    return true;
}

//If specefied cell is selected
bool Board::cellIsSelected(int x, int y){
    if(selectedCell.x == x && selectedCell.y == y){
        return true;
    }

    return false;
}

void Board::selectCell(int x, int y){
    if(!cells[x][y].occupied) return;

    std::cout << "Selecting cell (" << x << ", " << y << ")\n";
    selectedCell.x = x;
    selectedCell.y = y;

    cells[x][y].click();
    pieces[cells[x][y].getPieceInCell()].click();

    invalidate();
}

void Board::performAction(Cell& clickedCell, GamePiece&  clickedPiece){
    Cell&       c_selectedCell    =     cells[selectedCell.x][selectedCell.y];
    GamePiece&  selectedPiece     =     pieces[c_selectedCell.getPieceInCell()];
    bool        actionPerformed   =     false;

    if(clickedCell.occupied){
        if(clickedPiece.getOwner() != selectedPiece.getOwner()){
            std::cout << "Board::clickCell(): ...Attack move\n";
            if(selectedPiece.canMove(*this, clickedCell, 1)){
                //remove piece from clicked cell
                clickedPiece.SetPosition(0, 0);
                clickedCell.removePieceFromCell();

                placePiece(c_selectedCell.getPieceInCell(), clickedCell.getGridX(), clickedCell.getGridY());
                actionPerformed     =   true;

                std::cout << "Board::clickCell(): \tPiece has jumped\n";
            }else{
                std::cout << "Board::clickCell(): \tPiece has not jumped\n";
            }
            deselect();
        }else{
            deselect();
            selectCell(clickedCell.getGridX(), clickedCell.getGridY());
        }
    }else{
        if(selectedPiece.canMove(*this, clickedCell, 0)){
            placePiece(c_selectedCell.getPieceInCell(), clickedCell.getGridX(), clickedCell.getGridY());
            actionPerformed     =   true;

            std::cout << "Board::clickCell(): Piece has moved\n";
        }else{
            std::cout << "Board::clickCell(): Piece has not moved\n";
        }

        deselect();
    }

    if(actionPerformed){
        selectedPiece.hasMoved = true;
        selectedPiece.click();
    }
}

//Make attacking possible
//sf::RenderWindow &App, int mouseX, int mouseY
 void Board::clickCell(){ //Event::Data e
    std::cout << "Hello thoough\n";
    /*
    int     clickedCellX    = getCellGridPosX(App,  mouseX,  mouseY);
    int     clickedCellY    = getCellGridPosY(App,  mouseX,  mouseY);

    int     selectedCellX   = selectedCell.x;
    int     selectedCellY   =   selectedCell.y;

    Cell&       clickedCell     = cells[clickedCellX][clickedCellY];
    Cell&       selectedCell    = cells[selectedCellX][selectedCellY];
    GamePiece&  selectedPiece   = pieces[selectedCell.getPieceInCell()];
    GamePiece&  clickedPiece   = pieces[clickedCell.getPieceInCell()];

    //If the cell we clicked on is selected, deselect the cell.
    if(!cellIsSelected()){ //If there is no cell selected
        std::cout << "Board::clickCell(): No cell selected\n";
        selectCell(clickedCellX, clickedCellY);
    }else if( cellIsSelected(clickedCellX, clickedCellY)){ //The cell clicked is the selected cell
        std::cout << "Board::clickCell(): Same cell clicked\n";
        deselect();
    }else if(cellIsSelected()){  //If we have made a selection (cell is selected), perform an action
        std::cout << "Board::clickCell(): Perform action...\n";
        performAction(clickedCell, clickedPiece);
    }else{ //Offboad click
        std::cout << "Board::clickCell(): Uh-oh, this is wrong. This should not happen. \n";
    }
    */
    return;
}

void Board::placePiece(int pIndex, int gX, int gY){
    pieces[pIndex].setGridPos(gX, gY);
    pieces[pIndex].SetPosition(getCellCenter(gX, gY));
    cells[selectedCell.x][selectedCell.y].removePieceFromCell();
    cells[gX][gY].putPieceInCell(pIndex);
}

void Board::deselect(){
    if(selectedCell.x != 9){
        std::cout << "Deselecting selected cell(" << selectedCell.x << ", " <<selectedCell.y <<")\n";

        int i = selectedCell.x;
        int j = selectedCell.y;

        cells[i][j].click();

        if(cells[i][j].occupied){
            pieces[cells[i][j].getPieceInCell()].click();
        }

        selectedCell.x = 9;
        selectedCell.y = 9;

        invalidate();
    }
}

void Board::createPieces(){
    Rules rules;

    int numPawns = rules.placement(GamePiece::Pawn);
    int numRooks = rules.placement(GamePiece::Rook);
    int numKnights = rules.placement(GamePiece::Knight);
    int numBishops = rules.placement(GamePiece::Bishop);
    int total = 0;

    //Create Player 1 Pawns
    for(int p1PawnCount = 0; p1PawnCount<numPawns; p1PawnCount++){
        pieces[p1PawnCount].index = p1PawnCount;
        pieces[p1PawnCount].setType(GamePiece::Pawn);
        pieces[p1PawnCount].setOwner(1);
        placePiece(p1PawnCount, p1PawnCount, 6);
    }

    total += numPawns;

    //Create Player 2 Pawns
    for(int p2pawnCount = 0; p2pawnCount<numPawns; p2pawnCount++){
        int index = p2pawnCount+total;
        pieces[index].index = index;
        pieces[index].setType(GamePiece::Pawn);
        pieces[index].setOwner(2);
        placePiece(index, p2pawnCount, 1);
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
        placePiece(index, xPos, 7);
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
        placePiece(index, xPos, 0);

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
        placePiece(index, xPos, 7);
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
        placePiece(index, xPos, 0);
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
        placePiece(index, xPos, 7);
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
        placePiece(index, xPos, 0);
    }

    total += numBishops;

    //p1 queen
    pieces[total].index = total;
    pieces[total].setType(GamePiece::Queen);
    pieces[total].setOwner(1);
    placePiece(total, 4, 7);

    total++;

    //p2 queen
    pieces[total].index = total;
    pieces[total].setType(GamePiece::Queen);
    pieces[total].setOwner(2);
    pieces[total].setGridPos(3, 0);
    pieces[total].SetPosition(getCellCenter(3, 0));
    cells[3][0].putPieceInCell(total);
    placePiece(total, 3, 0);

    total++;

    //p1 king
    pieces[total].setType(GamePiece::King);
    pieces[total].setOwner(1);
    pieces[total].setGridPos(3, 7);
    pieces[total].SetPosition(getCellCenter(3, 7));
    cells[3][7].putPieceInCell(total);
    placePiece(total, 3, 7);

    total++;

    //p2 king
    pieces[total].setType(GamePiece::King);
    pieces[total].setOwner(2);
    pieces[total].setGridPos(4, 0);
    pieces[total].SetPosition(getCellCenter(4, 0));
    cells[4][0].putPieceInCell(total);
    placePiece(total, 4, 0);

    total++;
}

void Board::invalidate(){
    std::cout << "Board::Invalidating\n";
    valid = false;
}

void Board::validate(){
    valid = true;
}

bool Board::isValid(){
    return valid;
}
