#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "MoveData.h"

Cell::Cell()
{
    m_isHighlighted = false;
    colorBlack      = sf::Color(102, 51, 0);
    colorBlack_h    = sf::Color(102, 132, 0);
    colorBlack_hr    = sf::Color(192, 51, 0);
    colorWhite      = sf::Color(255, 255, 204);
    colorWhite_h    = sf::Color(174, 255, 141);
    colorWhite_hr    = sf::Color(255, 129, 96);
    colorHighlight  = sf::Color(100, 200, 100);
    EnableFill(true);
    EnableOutline(false);
    SetPosition(0.f, 0.f);
    clicked = false;
    occupied = false;
    inCell = NULL;
}

Cell::~Cell(){

}

sf::Vector2f Cell::GetCenter(){
    return sf::Vector2f(GetPosition().x+(getWidth()/2), GetPosition().y+(getHeight()/2));
}

void Cell::putPieceInCell(int piece){
    if(!occupied){
        inCell = piece;
        occupied = true;
    }
}

void Cell::removePiece(){
    occupied = false;
    inCell = NULL;
}


int Cell::getPieceInCell(){
    return inCell;
}

void Cell::setGridPos(int x, int y){
    gridPos.x   =   x;
    gridPos.y   =   y;
}

void Cell::setGridPos(sf::Vector2i coord){
    gridPos = coord;
}

int Cell::getGridX(){
    return gridPos.x;
}

int Cell::getGridY(){
    return gridPos.y;
}

void Cell::click(){
    if(clicked){
        clicked = false;
    }else{
        clicked = true;
    }

    outline(clicked);
}

void Cell::outline(bool on){
    EnableOutline(on);
    SetOutlineWidth(-2);

    setOutlineColor(colorHighlight);
    invalidate();
}

void Cell::highlightOn(bool attackMove){
    m_isHighlighted = true;
    sf::Color black, white;
    int gridX = gridPos.x, gridY = gridPos.y;

    if(attackMove){
        black = colorBlack_hr;
        white = colorWhite_hr;
    }else{
        black = colorBlack_h;
        white = colorWhite_h;
    }

    if(gridX%2 == 0){
        if(gridY%2 != 0){
            setColor( white);
        }else{
            setColor( black);
        }
    }else{
        if(gridY%2 != 0){
            setColor( black);
        }else{
            setColor( white);
        }
    }

    invalidate();
}

void Cell::highlightOff(){
    m_isHighlighted = false;

    setToBoardColor();
}

//Sets the color the cell should be on the board, i.e. white or black. Or if it is clicked, highlight the cell
void Cell::setToBoardColor(){
    if(m_isHighlighted){ return; }
    int gridX = gridPos.x, gridY = gridPos.y;

    if(gridX%2 == 0){
        if(gridY%2 != 0){
            setColor( colorWhite);
        }else{
            setColor( colorBlack);
        }
    }else{
        if(gridY%2 != 0){
            setColor( colorBlack);
        }else{
            setColor( colorWhite);
        }
    }

    invalidate();
}

