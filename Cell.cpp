#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Cell::Cell()
{
    colorBlack      = sf::Color(102, 51, 0);
    colorWhite      = sf::Color(255, 255, 204);
    colorHighlight  = sf::Color(100, 200, 100);
    EnableFill(true);
    EnableOutline(false);
    SetPosition(0.f, 0.f);
    clicked = false;
    important = false;
    occupied = false;
    inCell = NULL;
}

void Cell::putPieceInCell(int piece){
    if(!occupied){
        inCell = piece;
        occupied = true;
    }
}

void Cell::removePieceFromCell(){
    occupied = false;
    inCell = NULL;
}


int Cell::getPieceInCell(){
    return inCell;
}

void Cell::setGridPos(int x, int y){
    gridX = x;
    gridY = y;
}

int Cell::getGridX(){
    return gridX;
}

int Cell::getGridY(){
    return gridY;
}

void Cell::click(){
    if(clicked){
        clicked = false;
        important = false;
    }else{
        clicked = true;
        important = true;
    }

    EnableOutline(clicked);
    SetOutlineWidth(-2);

    for(int i=0; i<4; i++){
        SetPointOutlineColor(i, colorHighlight);
    }
}

//Sets the color the cell should be on the board, i.e. white or black. Or if it is clicked, highlight the cell
void Cell::setToBoardColor(){
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
}

