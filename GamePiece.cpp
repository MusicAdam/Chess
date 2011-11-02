#include "GamePiece.h"
#include "Board.h"

GamePiece::GamePiece()
{

    SetCenter(25, 25);
    hasMoved = false;
    selected = false;
}

void GamePiece::setGridPos(int x, int y){
    gridX = x;
    gridY = y;
}

int GamePiece::getGridX(){
    return gridX;
}

int GamePiece::getGridY(){
    return gridY;
}

void GamePiece::setType(int nType){
    type = nType;
}

int GamePiece::getType(){
    return type;
}

void GamePiece::setOwner(int player){
    owner = player;

    if(owner == 2){
        moveOrientation = 1;
        SetColor(sf::Color(0, 0, 0, 255));
    }else{
        moveOrientation = -1;
    }
}

int GamePiece::getOwner(){
    return owner;
}

void GamePiece::click(){
    if(selected){
        selected = false;
        SetScale(1.f, 1.f);
    }else{
        selected = true;
        SetScale(1.2, 1.2);
    }
}

//This function handles movement
//This can be used to check for proper attack movement if movementType is set to attack
bool GamePiece::canMove(Board& gBoard, Cell& toCell, int moveType=NULL){
    if(moveType == NULL){
        moveType = 0;
    }

    MoveData MoveData(type);

    int moveDirectionX = ((toCell.getGridX() - gBoard.selectedCell.x) < 0) ? -1 : 1;
    int moveDirectionY = ((toCell.getGridY() - gBoard.selectedCell.y) < 0) ? -1 : 1;
    int distanceX   =   (toCell.getGridX() - gBoard.selectedCell.x)*moveDirectionX;
    int distanceY   =   (toCell.getGridY() - gBoard.selectedCell.y)*moveDirectionY;


    //Check to see if the piece can go the distance
    //Also pawn's unique jump
    if(type == GamePiece::Pawn){
        if(moveType == 0){
            if(!hasMoved){
                MoveData.distance.y = 2;
            }else{
               // MoveData.distance.y = 1;
            }
        }else{
            MoveData.direction = MoveData::Diagonal;
            MoveData.distance.x = 1;
            MoveData.distance.y = 1;
        }
    }

    int activeMoveDirection; //For pieces that can move in the all direction (excluding nights) this tells the direction checker which direction the piece is actually moving diag or perp
    if(type == GamePiece::Queen){
        if((distanceX == 0 && distanceY != 0) || (distanceX != 0 && distanceY == 0)){
            activeMoveDirection = MoveData::Perpendicular;
        }else if(distanceX==distanceY){
            activeMoveDirection = MoveData::Diagonal;
        }else if(distanceX!=distanceY && distanceX != 0  && distanceY != 0){
            return false;
        }
    }else{
        activeMoveDirection = MoveData.direction;
    }

    //Check to see if piece can move in the direction it is trying to move

    switch(activeMoveDirection){
        case MoveData::Forward:
            if((distanceX != 0) || (moveDirectionY != moveOrientation)){
                std::cout << "GamePiece::canMove(): Piece can only move forward!\n";
                return false;
            }
            break;
        case MoveData::Diagonal:
            std::cout << "DistanceX( " << distanceX << " ) == DistanceY ( " << distanceY << " )\n";
            if(distanceX != distanceY){
                std::cout << "GamePiece::canMove(): Piece can only move diagonally!\n";
                return false;
            }
            break;
        case MoveData::Perpendicular:
            if(distanceX != 0 && distanceY != 0){
                std::cout << "GamePiece::canMove(): Piece can only move perpendicularly!\n";
                return false;
            }
            break;
        default:
            break;
    }

    if(MoveData.distance.x != -1){
        if((distanceX > MoveData.distance.x) || (distanceY > MoveData.distance.y)){
            std::cout << "GamePiece::canMove(): Cell is out of the piece's range!\n";
            return false;
        }
    }

    //Try to find a clear path
    try
    {
        //pathfinding logic

        int checkX=1*moveDirectionX;
        int checkY=1*moveDirectionY;
        int movedX=1;
        int movedY=1;
        int checkCellX=gBoard.selectedCell.x;
        int checkCellY=gBoard.selectedCell.y;
        int knightTry = 1;


        do{
            //Special move case if piece is a knight
            if(type == GamePiece::Knight){
                if((distanceX == 2) && (distanceY == 1)){
                    if(movedX <= distanceX){
                        checkCellX += checkX;
                        movedX++;

                        incrementCoord(checkX, NULL, moveDirectionX, NULL);
                    }else if(movedY <= distanceY){
                        checkCellY += checkY;
                        movedY++;

                        incrementCoord(checkY, NULL, moveDirectionY, NULL);
                    }else{
                        break;
                    }
                }else if((distanceX == 1) && (distanceY == 2)){
                    if(movedY <= distanceY){
                        checkCellY += checkY;
                        movedY++;

                        incrementCoord(NULL, checkY, NULL, moveDirectionY);
                    }else if(movedX <= distanceX){
                        checkCellX += checkX;
                        movedX++;

                        incrementCoord(checkX, NULL, moveDirectionX, NULL);
                    }else{
                        break;
                    }
                }else{
                    std::cout << "GamePiece::canMove(): Knight can not move in that way\n";
                    throw Exception::Path;
                }
            }else if(distanceX == distanceY){ //Diagonal movement
                std::cout << "Diag\n";
                if(movedY != distanceY){
                    checkCellY += checkY;
                    movedY++;
                    checkCellX += checkX;
                    movedX++;

                    incrementCoord(checkX, checkY, moveDirectionX, moveDirectionY);
                }else{
                    break;
                }
            }else{
                if(movedY <= distanceY){
                    checkCellY += checkY;
                    movedY++;

                    incrementCoord(NULL, checkY, NULL, moveDirectionY);
                }else if(movedX <= distanceX){
                    checkCellX += checkX;
                    movedX++;

                    incrementCoord(checkX, NULL, moveDirectionX, NULL);
                }else{
                    break;
                }
            }


            std::cout << "GamePiece::canMove(): Checking cell ( " << checkCellX << ", " << checkCellY << " ) Cell occupied: " << gBoard.getCell(checkCellX, checkCellY).occupied << "\n";

            if(moveType == 1){
            }else{
                if(gBoard.getCell(checkCellX, checkCellY).occupied){
                    if(type != Knight){
                        std::cout << "GamePiece::canMove(): Cell is occupied, can not move through another piece.\n";
                        throw Exception::Path;
                    }
                }

                if(movedY > 9 || movedX > 9){
                    std::cout << "GamePiece::canMove(): Infinite loop!\n";
                    throw Exception::Fatal;
                }
            }
        }while(movedY != distanceY || movedX != distanceX);

    }

    catch(int ePath) //Catch pathfinding exception
    {
        switch(ePath){
            case Exception::Path:
                std::cout << "GamePiece::canMove(): A pathfinding exception has occured.\n";
                return false;
            case Exception::Fatal:
                std::cout << "GamePiece::canMove(): A fatal exception has occured.\n";
                return false;
                break;
        }

    }

    return true;
}

//private
void GamePiece::incrementCoord(int* x, int* y, int dirX, int dirY){
    if(dirX != NULL){
        if(dirX < 0){
            x--;
        }else{
            x++;
        }
    }

    if(dirY != NULL){
        if(dirY < 0){
            y--;
        }else{
            y++;
        }
    }
}
