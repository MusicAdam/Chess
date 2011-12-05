#include "TileMap.h"
#include "Board.h"
#include "RenderHandler.h"
#include "Cell.h"

TileMap::TileMap(int cellCount, int cellSize)
{
    m_cellCount      = cellCount;
    m_cellSize       = cellSize;
    m_size           = m_cellCount*m_cellSize;

    m_clickCoord = sf::Vector2i(-1, -1);
}

TileMap::~TileMap()
{
    //dtor
}

void TileMap::load(){
    sf::Vector2f cellPos;

        //Set up cell array
    for(int x=0; x<m_cellCount; x++){
        for(int y=0; y<m_cellCount; y++){
            cellPos = getCellPosition(sf::Vector2i(x, y));
            cells[x][y].setGridPos(x, y);
            cells[x][y].setSize(m_cellSize, m_cellSize);
            cells[x][y].SetX(cellPos.x);
            cells[x][y].SetY(cellPos.y);
            cells[x][y].setToBoardColor();

            RenderHandler::Get()->addComponent(cells[x][y], 3);
        }
    }
}

void TileMap::SetPosition(float x, float y){
    m_x = x;
    m_y = y;
}

sf::Vector2f TileMap::getCellPosition(sf::Vector2i coords){
    return sf::Vector2f(((coords.x*m_cellSize)+m_x), ((coords.y*m_cellSize)+m_y));
}

int TileMap::MapSize(){
    return m_size;
}

Cell& TileMap::GetCell(sf::Vector2i coord) throw(TMapException){
    std::string error;

    if(CheckGridBounds(coord)){
        if(cells.find(coord.x) != cells.end()){
            if(cells[coord.x].find(coord.y) != cells[coord.x].end()){
                return cells[coord.x][coord.y];
            }else{
                error = "Y Coordinate does not exist";
            }
        }else{
            error = "X coordinate does not exist";
        }
    }else{
        error = "Coordinates are out of bounds";
    }
    TMapException newE;
    newE.c = coord;
    newE.type = TMapException::NULL_CELL;
    newE.why = error;
    throw newE;
}

Cell& TileMap::GetSelection() throw(TMapException){
    TMapException newError;

    if(m_clickCoord.x != -1 && m_clickCoord.y != -1){
        try{
            Cell returnCell = GetCell(m_clickCoord);
            return returnCell;
        }
        catch(TMapException e){
            newError.why = e.why;
        }
    }else{
        newError.type = TMapException::NO_SELECTION;
        newError.why = "No cell is selected";
    }

    throw newError;
}

bool TileMap::CheckGridBounds(sf::Vector2i coord){
    if((coord.x >= 0 && coord.x < m_cellCount) && (coord.y >= 0 && coord.y < m_cellCount))
        return true;

    return false;
}

bool TileMap::CheckPixelBounds(sf::Vector2f coord){
    if((coord.x >= m_x && coord.x < m_x + MapSize()) && (coord.y > m_y && coord.y < m_y+MapSize()))
        return true;

    return false;
}

sf::Vector2i TileMap::GetGridFromPixel(sf::Vector2f coord){
    int x = (coord.x - ((RenderHandler::Window()->GetWidth()/2)-(MapSize()/2)))/m_cellSize;
    int y = (coord.y - ((RenderHandler::Window()->GetHeight()/2)-(MapSize()/2)))/m_cellSize;

    return sf::Vector2i(x, y);
}

bool TileMap::Click(sf::Vector2f mCoord){
    if(CheckPixelBounds(mCoord)){
        try{
            Cell& clickedCell = GetCell(GetGridFromPixel(mCoord));

            if(clickedCell.gridPos == m_clickCoord){
                Deselect();
            }else{
                if(!clickedCell.clicked){
                    Deselect();
                    clickedCell.click();
                    Select(clickedCell.gridPos);
                }
            }
        }

        catch(TMapException e){
            if(e.type == TMapException::NULL_CELL){
                std::cout << "GetCell("<< e.c.x <<", " << e.c.y << "):> FAILED: " << e.why << "\n";
            }
        }

    }else{
        std::cout << "Click is out of bounds!\n";
    }

    return true;
}



void TileMap::Select(sf::Vector2i c){
    if(!CheckGridBounds(c)) return;

    m_clickCoord.x = c.x;
    m_clickCoord.y = c.y;
}

void TileMap::Deselect() throw(){
    if(!CheckGridBounds(m_clickCoord)) return;

    try{
        GetCell(m_clickCoord).click();
    }

    catch(...){
        std::cout << "Cannot deselect cell: The selected cell does not exist!\n";
    }

    m_clickCoord.x = -1;
    m_clickCoord.y = -1;
}

void TileMap::unload(){
    Cell* tmpCell;

    for(int x=0; x<m_cellCount; x++){
        for(int y=0; y<m_cellCount; y++){
            tmpCell = &cells[x][y];
            RenderHandler::Get()->removeComponent(tmpCell);
        }
    }

    cells.clear();
}
