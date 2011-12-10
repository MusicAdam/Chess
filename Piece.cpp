#include "Piece.h"

#include "Board.h"
#include "Square.h"

Piece::Piece()
{
    SetCenter(25, 25);
    hasMoved = false;
    selected = false;
    SetState(STATE_SLEEP);
}

Piece::~Piece(){
}

void Piece::_setImage(const std::string& fname){
     if(Image.LoadFromFile(fname)){
        SetImage(Image);
     }
}

sf::Vector2f Piece::GetPos(){
    return sf::Vector2f(currentSquare->gridPos.x, currentSquare->gridPos.y);
}

void Piece::setGridPos(sf::Vector2i coord){
    if(!isAlive()) return;

    try{
        currentSquare = Board::Get()->GetSquare(coord);
        currentSquare->PlacePiece(this);
        SetPosition(currentSquare->GetCenter());
    }

    catch(TileMap::TMapException e){
        std::cout << "Piece::setGridPos(" << coord.x << ", " << coord.y << ") :> Exception \"" << e.type << "\" encountered, " << e.why << "\n";
    }
}

void Piece::setType(int nType){
    type = nType;

    switch(nType){
        case Piece::Pawn:
            _setImage("pawn.png");
            break;
        case Piece::Bishop:
            _setImage("bishop.png");
            break;
        case Piece::Rook:
            _setImage("rook.png");
            break;
        case Piece::Knight:
            _setImage("knight.png");
            break;
        case Piece::King:
            _setImage("king.png");
            break;
        case Piece::Queen:
            _setImage("queen.png");
            break;
    }


}

Square* Piece::GetSquare(){
    return currentSquare;
}

int Piece::getType(){
    return type;
}

void Piece::setOwner(int player){
    owner = player;

    if(owner == 2){
        moveOrientation = 1;
        SetColor(sf::Color(0, 0, 0, 255));
    }else{
        moveOrientation = -1;
    }
}

Player* Piece::Owner(){
    if(owner == 1){
        return Player::One();
    }else{
        return Player::Two();
    }
}

void Piece::click(){
    if(selected){
        selected = false;
        SetScale(1.f, 1.f);
    }else{
        selected = true;
        SetScale(1.2, 1.2);
    }
}

void Piece::kill(){
    currentSquare = NULL;
    sleep();
    SetState(STATE_DEAD);
}

bool Piece::isAlive(){
    if(GetState() == STATE_DEAD){
        return false;
    }

    return true;
}

//Handle attacks..
bool Piece::Move(MoveData MoveData){
    if(!MoveData.isPossible()){
        return false;
    }

    if(MoveData.isAttackMove()){
        std::cout << index << "(Player: " << Owner()->id() << ") is jumping " << Board::Get()->GetSquare(MoveData.toSquare)->GetPiece()->index << " (Player: " << Board::Get()->GetSquare(MoveData.toSquare)->GetPiece()->Owner()->id() << ")\n";
        Board::Get()->GetSquare(MoveData.toSquare)->GetPiece()->SetPosition(0, 0);
        Board::Get()->GetSquare(MoveData.toSquare)->GetPiece()->kill();
        Board::Get()->GetSquare(MoveData.toSquare)->Empty();
    }

    //Tell the current Square piece is leaving
    Board::Get()->GetSquare(MoveData.fromSquare)->Empty();

    //Tell the new Square we are ariving, and to position us corrently
    setGridPos(MoveData.toSquare);
    hasMoved    =   true;
    click();

    //Need redraw
    RenderHandler::Get()->invalidate();


    return true;
}

/********************************************************************\
                "Stores MoveData if move is possible"
            CLASS:      Piece
            NAME:       StoreMove
            PARAMS:     MoveData&
            RETRUNS:     bool

            Returns true if the item was stored
/*******************************************************************/
bool Piece::RememberPath(MoveData& MoveData){
    PossibleMoves.push_back(MoveData);

    return true;
}

void Piece::FindPossibleMoves(){
    vector<MoveData> ugh;   //I wish vectors could be null
    sf::Vector2i vect;
    vect.x = NULL;
    FindPossibleMoves(vect, ugh);
}

void Piece::FindPossibleMoves(sf::Vector2i from, vector<MoveData>& storage){
    MoveData rules(*this);

    int dir=0;
    sf::Vector2i fromSquare;
    sf::Vector2i checkSquare;
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


    if(getType() == Piece::Knight){

        sf::Vector2i specialMove;
        //A knight can make 8 possible moves
        for(int move=0; move < 8; move++){
            newMove = MoveData::MoveData(*this);

            if(useCurrentPosition){
                newMove.fromSquare = currentSquare->gridPos;
                checkSquare = currentSquare->gridPos;
            }else{
                newMove.fromSquare = from;
                checkSquare = from;
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

            checkSquare.x += specialMove.x;
            checkSquare.y += specialMove.y;

            if(!Board::Get()->CheckGridBounds(checkSquare)) continue;

            newMove.toSquare = checkSquare;

            if(newMove.isPossible()){
                if(useInternalStorage){
                    RememberPath(newMove);
                }else{
                    storage.push_back(newMove);
                }
            }
        }

    }else{

        if(getType() == Piece::Pawn){
            newMove = MoveData::MoveData(*this);
            if(useCurrentPosition){
                newMove.fromSquare = currentSquare->gridPos;
                checkSquare = currentSquare->gridPos;
            }else{
                newMove.fromSquare = from;
                checkSquare = from;
            }

            //check for left attack
            checkSquare.x -= 1;
            checkSquare.y += Player::Active()->forward();

            newMove.toSquare = checkSquare;

            if(newMove.isPossible()){
                if(useInternalStorage){
                    RememberPath(newMove);
                }else{
                    storage.push_back(newMove);
                }
            }

            newMove = MoveData::MoveData(*this);
            if(useCurrentPosition){
                newMove.fromSquare = currentSquare->gridPos;
                checkSquare = currentSquare->gridPos;
            }else{
                newMove.fromSquare = from;
                checkSquare = from;
            }

            //check for right attack
            checkSquare.x += 1;
            checkSquare.y += Player::Active()->forward();

            newMove.toSquare = checkSquare;

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
                    newMove.fromSquare = currentSquare->gridPos;
                    checkSquare = currentSquare->gridPos;
                }else{
                    newMove.fromSquare = from;
                    checkSquare = from;
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
                    checkSquare.x += testOrientation.x;
                    checkSquare.y += testOrientation.y;

                    if(Board::Get()->CheckGridBounds(checkSquare)){
                        newMove.toSquare = checkSquare;

                        if(newMove.isPossible()){
                            if(useInternalStorage){
                                RememberPath(newMove);
                            }else{
                                storage.push_back(newMove);
                            }

                            checkSquare = newMove.toSquare;
                            newMove = MoveData::MoveData(*this);
                            if(useCurrentPosition){
                                newMove.fromSquare = currentSquare->gridPos;
                            }else{
                                newMove.fromSquare = from;
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

vector<MoveData> Piece::FindPossibleMoves(sf::Vector2i fromSquare){
    vector<MoveData> storage;

    FindPossibleMoves(fromSquare, storage);

    return storage;
}

void Piece::showPossibleMovesOnBoard(){
    vector<MoveData>::iterator it;

    for(it = PossibleMoves.begin(); it<PossibleMoves.end(); it++){
        Board::Get()->highlightSquare((*it).toSquare.x, (*it).toSquare.y, (*it).isAttackMove());
    }
}

void Piece::hidePossibleMovesOnBoard(){
    vector<MoveData>::iterator it;

    for(it = PossibleMoves.begin(); it<PossibleMoves.end(); it++){
        Board::Get()->hideSquareHighlight((*it).toSquare.x, (*it).toSquare.y);
    }
}

int Piece::GetState(){
    return m_state;
}

void Piece::SetState(int state){
    m_state = state;
}

void Piece::wake(){
    if(isAwake()) return;

    FindPossibleMoves();
    SetState(STATE_IDLE);
}

void Piece::sleep(){
    PossibleMoves.clear();
    SetState(STATE_SLEEP);
}

bool Piece::isAwake(){
    if(GetState() == STATE_SLEEP)
        return false;

    return true;
}

bool Piece::isIdle(){
    if(GetState() == STATE_IDLE)
        return true;

    return false;
}

//Clear possible moves
//At this point, the active player is the player whose turn is beginning
void Piece::turn(){


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

void Piece::think() {
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

void Piece::incrementCoord(int* xPtr, int* yPtr, int orientationX, int orientationY){
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





