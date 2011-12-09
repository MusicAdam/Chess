#include "TileMap.h"
#include "Board.h"
#include "RenderHandler.h"
#include "Square.h"
#include <sstream>

TileMap::TileMap(int SquareCount, int SquareSize)
{
    m_SquareCount      = SquareCount;
    m_SquareSize       = SquareSize;
    m_size           = m_SquareCount*m_SquareSize;

    m_clickCoord = sf::Vector2i(-1, -1);
}

TileMap::~TileMap()
{
    //dtor
}

void TileMap::load(){
    sf::Vector2f SquarePos;

    int counter = 0;
        //Set up Square array
    for(int x=0; x<m_SquareCount; x++){
        for(int y=0; y<m_SquareCount; y++){
            Squares[x][y] = new Square();
            SquarePos = getSquarePosition(sf::Vector2i(x, y));
            Squares[x][y]->setGridPos(x, y);
            Squares[x][y]->SetSize(m_SquareSize, m_SquareSize);
            Squares[x][y]->SetX(SquarePos.x);
            Squares[x][y]->SetY(SquarePos.y);
            Squares[x][y]->setToBoardColor();

            RenderHandler::Get()->addComponent(*Squares[x][y], 3);
            counter++;

            std::cout << counter << std::endl;
        }
    }
}

void TileMap::SetPosition(float x, float y){
    m_x = x;
    m_y = y;
}

sf::Vector2f TileMap::getSquarePosition(sf::Vector2i coords){
    return sf::Vector2f(((coords.x*m_SquareSize)+m_x), ((coords.y*m_SquareSize)+m_y));
}

int TileMap::MapSize(){
    return m_size;
}

Square* TileMap::GetSquare(sf::Vector2i coord) throw(TMapException){
    std::stringstream   error_stream;

    if(CheckGridBounds(coord)){
        if(Squares.find(coord.x) != Squares.end()){
            if(Squares[coord.x].find(coord.y) != Squares[coord.x].end()){
                return Squares[coord.x][coord.y];
            }else{
                error_stream << "Y coordinate ";
                error_stream << coord.y;
                error_stream << " does not exist";
            }
        }else{
            error_stream << "X coordinate ";
            error_stream << coord.x;
            error_stream << " does not exist";
        }
    }else{
        error_stream << "Coordinate ";
        error_stream << coord.x;
        error_stream << ", ";
        error_stream << coord.y;
        error_stream << " is out of bounds";
    }

    TMapException newE;
    newE.c = coord;
    newE.type = TMapException::NULL_SQUARE;
    newE.why = error_stream.str();
    throw newE;
}

Square* TileMap::GetSelection() throw(TMapException){
    TMapException newError;

    if(m_clickCoord.x != -1 && m_clickCoord.y != -1){
        try{
            Square* returnSquare = GetSquare(m_clickCoord);
            return returnSquare;
        }

        catch(TMapException e){
            newError.why = e.why;
            newError.type = e.type;
        }
    }else{
        newError.type = TMapException::NO_SELECTION;
        newError.why = "No Square is selected";
    }

    throw newError;
}

bool TileMap::CheckGridBounds(sf::Vector2i coord){
    if((coord.x >= 0 && coord.x < m_SquareCount) && (coord.y >= 0 && coord.y < m_SquareCount))
        return true;

    return false;
}

bool TileMap::CheckPixelBounds(sf::Vector2f coord){
    if((coord.x >= m_x && coord.x < m_x + MapSize()) && (coord.y > m_y && coord.y < m_y+MapSize()))
        return true;

    return false;
}

sf::Vector2i TileMap::GetGridFromPixel(sf::Vector2f coord){
    int x = (coord.x - ((RenderHandler::Window()->GetWidth()/2)-(MapSize()/2)))/m_SquareSize;
    int y = (coord.y - ((RenderHandler::Window()->GetHeight()/2)-(MapSize()/2)))/m_SquareSize;

    return sf::Vector2i(x, y);
}

bool TileMap::Click(sf::Vector2f mCoord){
    try{
        Square* clickedSquare = GetSquare(GetGridFromPixel(mCoord));

        if(clickedSquare->gridPos == m_clickCoord){
            Deselect();
        }else{
            if(!clickedSquare->clicked){
                Deselect();
                clickedSquare->click();
                Select(clickedSquare->gridPos);
            }
        }
    }

    catch(TMapException e){
        if(e.type == TMapException::NULL_SQUARE){
            std::cout << "Click("<< mCoord.x <<", " << mCoord.y << "):> FAILED: " << e.why << "\n";
        }
    }

    return true;
}



void TileMap::Select(sf::Vector2i c){
    if(!CheckGridBounds(c)) return;

    m_clickCoord.x = c.x;
    m_clickCoord.y = c.y;

    std::cout << "Square " << c.x << ", " << c.y << " has been selected\n";
}

void TileMap::Deselect() throw(){
    if(!CheckGridBounds(m_clickCoord)) return;

    try{
        int tmpx = m_clickCoord.x;
        int tmpy = m_clickCoord.y;

        GetSquare(m_clickCoord)->click();
        m_clickCoord.x = -1;
        m_clickCoord.y = -1;

        std::cout << "Square " << tmpx << ", " << tmpy << " has been deselected\n";
    }

    catch(...){
        std::cout << "Cannot deselect Square: The selected Square does not exist!\n";
    }
}

void TileMap::unload(){
    Square* tmpSquare;

    for(int x=0; x<m_SquareCount; x++){
        for(int y=0; y<m_SquareCount; y++){
            tmpSquare = Squares[x][y];
            RenderHandler::Get()->removeComponent(tmpSquare);
        }
    }

    Squares.clear();
}
