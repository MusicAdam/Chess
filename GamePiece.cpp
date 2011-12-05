#include "GamePiece.h"
#include "Board.h"

GamePiece::GamePiece()
{
    SetCenter(25, 25);
    hasMoved = false;
    selected = false;
    SetState(STATE_SLEEP);
}

GamePiece::~GamePiece(){
}

void GamePiece::_setImage(const std::string& fname){
     if(Image.LoadFromFile(fname)){
        SetImage(Image);
     }
}

void GamePiece::setGridPos(sf::Vector2i coord){
    try{
        currentCell = Board::Get()->GetCell(coord);
        SetPosition(currentCell.GetCenter());

        std::cout << "Piece placed at coord: " << coord.x << "(Pixel: " << currentCell.GetCenter().x << "), "<< coord.y << "(Pixel: " << currentCell.GetCenter().y << ")\n";
    }

    catch(TileMap::TMapException e){
        std::cout << "GamePiece::setGridPos(" << coord.x << ", " << coord.y << ") :> Exception \"" << e.type << "\" encountered, " << e.why << "\n";
    }
}

void GamePiece::setType(int nType){
    type = nType;

    switch(nType){
        case GamePiece::Pawn:
            _setImage("pawn.png");
            break;
        case GamePiece::Bishop:
            _setImage("bishop.png");
            break;
        case GamePiece::Rook:
            _setImage("rook.png");
            break;
        case GamePiece::Knight:
            _setImage("knight.png");
            break;
        case GamePiece::King:
            _setImage("king.png");
            break;
        case GamePiece::Queen:
            _setImage("queen.png");
            break;
    }


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

Player* GamePiece::Owner(){
    if(owner == 1){
        return Player::One();
    }else{
        return Player::Two();
    }
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

void GamePiece::kill(){
    sleep();
    SetState(STATE_DEAD);
}

bool GamePiece::isAlive(){
    if(GetState() == STATE_DEAD){
        return false;
    }

    return true;
}

//Handle attacks..
bool GamePiece::Move(MoveData MoveData){
    if(!MoveData.isPossible()){
        return false;
    }

    if(MoveData.isAttackMove()){
        Board::Get()->killPiece(Board::Get()->getCell(MoveData.toCell.x, MoveData.toCell.y).getPieceInCell());
        Board::Get()->removePieceFromCell(MoveData.toCell);
    }

    //Tell the current cell piece is leaving
    Board::Get()->removePieceFromCell(MoveData.fromCell);

    //Tell the new cell we are ariving, and to position us corrently
    Board::Get()->placePieceInCell(index, MoveData.toCell);

    //Record our move..
    currentCell = Board::Get()->GetCell(MoveData.toCell);
    hasMoved    =   true;

    //Need redraw
    RenderHandler::Get()->invalidate();


    return true;
}

/********************************************************************\
                "Stores MoveData if move is possible"
            CLASS:      GamePiece
            NAME:       StoreMove
            PARAMS:     MoveData&
            RETRUNS:     bool

            Returns true if the item was stored
/*******************************************************************/
bool GamePiece::RememberPath(MoveData& MoveData){
    PossibleMoves.push_back(MoveData);

    return true;
}

void GamePiece::FindPossibleMoves(){
    vector<MoveData> ugh;   //I wish vectors could be null
    sf::Vector2i vect;
    vect.x = NULL;
    FindPossibleMoves(vect, ugh);
}

void GamePiece::FindPossibleMoves(sf::Vector2i from, vector<MoveData>& storage){
    MoveData rules(*this);

    int dir=0;
    sf::Vector2i fromCell;
    sf::Vector2i checkCell;
    sf::Vector2i testOrientation;
    bool collisionDetected;
    bool useInternalStorage = true;
    bool useCurrentPosition = true;
    MoveData newMove(*this);
    int flag = 0;

    if(from.x != NULL){
        useInternalStorage = false;
        useCurrentPosition = false;
    }

    /*
        Before we do any dynamic checking, we should check special cases first.
            Pawns: Check to see if an attack move can be made
            Knights: Skip dynamic checking, knights move idependentally of this dynmaic check
    */


    if(getType() == GamePiece::Knight){

        sf::Vector2i specialMove;
        //A knight can make 8 possible moves
        for(int move=0; move < 8; move++){
            newMove = MoveData::MoveData(*this);

            if(useCurrentPosition){
                newMove.fromCell = currentCell.gridPos;
                checkCell = currentCell.gridPos;
            }else{
                newMove.fromCell = from;
                checkCell = from;
            }

            switch(move){
                case 0:
                    specialMove.x = -2;
                    specialMove.y = 1;
                    break;
                case 1:
                    specialMove.x = -2;
                    specialMove.y = -1;
                    break;
                case 2:
                    specialMove.x = 2;
                    specialMove.y = 1;
                    break;
                case 3:
                    specialMove.x = 2;
                    specialMove.y = -1;
                    break;
                case 4:
                    specialMove.x = 1;
                    specialMove.y = 2;
                    break;
                case 5:
                    specialMove.x = -1;
                    specialMove.y = 2;
                    break;
                case 6:
                    specialMove.x = 1;
                    specialMove.y = -2;
                    break;
                case 7:
                    specialMove.x = -1;
                    specialMove.y = -2;
                    break;
            }

            checkCell.x += specialMove.x;
            checkCell.y += specialMove.y;

            if(!Board::Get()->cellIsInBounds(checkCell)) continue;

            newMove.toCell = checkCell;

            if(newMove.isPossible()){
                if(useInternalStorage){
                    RememberPath(newMove);
                }else{
                    storage.push_back(newMove);
                }
            }
        }

    }else{

        if(getType() == GamePiece::Pawn){
            newMove = MoveData::MoveData(*this);
            if(useCurrentPosition){
                newMove.fromCell = currentCell.gridPos;
                checkCell = currentCell.gridPos;
            }else{
                newMove.fromCell = from;
                checkCell = from;
            }

            //check for left attack
            checkCell.x -= 1;
            checkCell.y += Player::Active()->forward();

            newMove.toCell = checkCell;

            if(newMove.isPossible()){
                if(useInternalStorage){
                    RememberPath(newMove);
                }else{
                    storage.push_back(newMove);
                }
            }

            newMove = MoveData::MoveData(*this);
            if(useCurrentPosition){
                newMove.fromCell = currentCell.gridPos;
                checkCell = currentCell.gridPos;
            }else{
                newMove.fromCell = from;
                checkCell = from;
            }

            //check for right attack
            checkCell.x += 1;
            checkCell.y += Player::Active()->forward();

            newMove.toCell = checkCell;

            if(newMove.isPossible()){
                if(useInternalStorage){
                    RememberPath(newMove);
                }else{
                    storage.push_back(newMove);
                }
            }
        }

        //Dynamically check movement
        for(int flagsw=0; flagsw<2; flagsw++){
            if(flagsw == 0){
                flag = MoveData::Perpendicular;
            }else{
                flag = MoveData::Diagonal;
            }

            if(!rules.hasFlag(flag)){
                continue;
            }

            //The main loop
            for(int dir=0; dir<4; dir++){
                newMove = MoveData::MoveData(*this);
                if(useCurrentPosition){
                    newMove.fromCell = currentCell.gridPos;
                    checkCell = currentCell.gridPos;
                }else{
                    newMove.fromCell = from;
                    checkCell = from;
                }

                if(flag == MoveData::Diagonal){
                    if(dir==0){
                        testOrientation.x = -1;
                        testOrientation.y = -1;
                    }else if(dir == 1){
                        testOrientation.x = 1;
                        testOrientation.y = -1;
                    }else if (dir == 2){
                        testOrientation.x = -1;
                        testOrientation.y = 1;
                    }else if(dir == 3){
                        testOrientation.x = 1;
                        testOrientation.y = 1;
                    }
                }else if(flag == MoveData::Perpendicular){
                    if(dir==0){
                        testOrientation.x = -1;
                        testOrientation.y = 0;
                    }else if(dir == 1){
                        testOrientation.x = 1;
                        testOrientation.y = 0;
                    }else if (dir == 2){
                        testOrientation.x = 0;
                        testOrientation.y = 1;
                    }else if(dir == 3){
                        testOrientation.x = 0;
                        testOrientation.y = -1;
                    }
                }


                collisionDetected = false;

                while(!collisionDetected){
                    //Need the rest to be inside of a while loops
                    checkCell.x += testOrientation.x;
                    checkCell.y += testOrientation.y;

                    if(Board::Get()->cellIsInBounds(checkCell)){
                        newMove.toCell = checkCell;

                        if(newMove.isPossible()){
                            if(useInternalStorage){
                                RememberPath(newMove);
                            }else{
                                storage.push_back(newMove);
                            }

                            checkCell = newMove.toCell;
                            newMove = MoveData::MoveData(*this);
                            if(useCurrentPosition){
                                newMove.fromCell = currentCell.gridPos;
                            }else{
                                newMove.fromCell = from;
                            }
                        }else{
                            collisionDetected = true;
                            break;
                        }
                    }else{
                        collisionDetected = true;
                        break;
                    }
                }
            }
        }
    }
}

vector<MoveData> GamePiece::FindPossibleMoves(sf::Vector2i fromCell){
    vector<MoveData> storage;

    FindPossibleMoves(fromCell, storage);

    return storage;
}

void GamePiece::showPossibleMovesOnBoard(){
    vector<MoveData>::iterator it;

    for(it = PossibleMoves.begin(); it<PossibleMoves.end(); it++){
        Board::Get()->highlightCell((*it).toCell.x, (*it).toCell.y, (*it).isAttackMove());
    }
}

void GamePiece::hidePossibleMovesOnBoard(){
    vector<MoveData>::iterator it;

    for(it = PossibleMoves.begin(); it<PossibleMoves.end(); it++){
        Board::Get()->hideCellHighlight((*it).toCell.x, (*it).toCell.y);
    }
}

int GamePiece::GetState(){
    return m_state;
}

void GamePiece::SetState(int state){
    m_state = state;
}

/*
    STATE_IDLE,   //Piece is ready to use
    STATE_TURN,//Piece is reset to default.
    STATE_SLEEP,   //Ready to be activated.

*/


void GamePiece::wake(){
    if(isAwake()) return;

    FindPossibleMoves();
    SetState(STATE_IDLE);
}

void GamePiece::sleep(){
    PossibleMoves.clear();
    SetState(STATE_SLEEP);
}

bool GamePiece::isAwake(){
    if(GetState() == STATE_SLEEP)
        return false;

    return true;
}

bool GamePiece::isIdle(){
    if(GetState() == STATE_IDLE)
        return false;

    return true;
}

//Clear possible moves
//At this point, the active player is the player whose turn is beginning
void GamePiece::turn(){


    //We want to wake all pieces if the AI is controlling.
    //Player will wake a piece when clicked.
    if(Player::Active()->isAI()){
        if(isAwake()){
            sleep(); //Reset them
            wake();
        }else{
            wake();
        }
    }else{
        //If its not the AI all pieces should start sleeping.
        if(isAwake()){
            sleep();
        }
    }
}

void GamePiece::think() {
    switch(Board::Get()->getState()){
        case Board::STATE_TURN:
            SetState(STATE_TURN);
            break;

    }

    switch(GetState()){
        case STATE_TURN:
            turn();
            break;

    }

}

/*********PRIVATE***********/

/**************************
    "Increment X and Y Coordinates"

    xPtr    pointer to the x we want to manipulate
    yPtr    ""  ""  ""  ""  ""  ""  ""

    orientationX    -1 for left 1 for right
    orientationY    -1 for up 1 for down

*************************/

void GamePiece::incrementCoord(int* xPtr, int* yPtr, int orientationX, int orientationY){
    if(orientationX != NULL){
        if(orientationX < 0){
            xPtr--;
        }else{
            xPtr++;
        }
    }

    if(orientationY != NULL){
        if(orientationY < 0){
            yPtr--;
        }else{
            yPtr++;
        }
    }
}





