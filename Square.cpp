#include "Square.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Board.h"
#include "MoveData.h"
#include "Piece.h"

Square::Square()
{
    m_highlightOn = false;
    colorBlack      = sf::Color(160, 60, 0);
    colorWhite      = sf::Color(255, 255, 204);
    colorGreen      = sf::Color(0, 155, 0, 255);
    colorGreen_b    = sf::Color(0, 255, 0, 255);
    colorRed        = sf::Color(153, 0, 0, 255);
    colorYellow     = sf::Color(200, 200, 0, 255);
    EnableFill(true);
    EnableOutline(false);
    SetPosition(0.f, 0.f);
    clicked = false;

    m_currentPiece      = NULL;
    m_currentMoveData   = NULL;

}

Square::~Square(){

}

void Square::setType(){
    if(gridPos.x%2 == 0){
        if(gridPos.y%2 != 0){
            m_type = WHITE;
        }else{
            m_type = BLACK;
        }
    }else{
        if(gridPos.y%2 != 0){
            m_type = BLACK;
        }else{
            m_type = WHITE;
        }
    }
}

sf::Vector2f Square::GetCenter(){
    return sf::Vector2f(GetPosition().x+(GetWidth()/2), GetPosition().y+(GetHeight()/2));
}

void Square::PlacePiece(Piece* piece){
    m_currentPiece  = piece;
}

void Square::Empty(){
    m_currentPiece  = NULL;
}


Piece* Square::GetPiece() throw(ChessException){
    ChessException newException;

    if(m_currentPiece == NULL){
        newException.type = ChessException::NullPiece;
        newException.why = "Square is empty";
    }else{
        return m_currentPiece;
    }

    throw(newException);
}

void Square::setGridPos(int x, int y){
    gridPos.x   =   x;
    gridPos.y   =   y;

    setType();
}

void Square::setGridPos(sf::Vector2i coord){
    setGridPos(gridPos.x, gridPos.y);
}

int Square::getGridX(){
    return gridPos.x;
}

int Square::getGridY(){
    return gridPos.y;
}

void Square::click(){
    if(clicked){
        clicked = false;
    }else{
        clicked = true;
    }

    outline(clicked);

    if(Occupied()){
        m_currentPiece->click();
    }

    invalidate();
}

void Square::outline(bool toggle){
    EnableOutline(toggle);

    if(toggle){
        SetOutlineWidth(-3);
        if(GetType() == WHITE){
            SetOutlineColor(colorGreen);
        }else{
            SetOutlineColor(colorGreen_b);
        }
    }

    invalidate();
}

bool Square::Occupied(){
    if(m_currentPiece == NULL){
        return false;
    }

    return true;
}

void Square::highlightOn(){
    m_highlightOn = true;
    sf::Color color = colorGreen;

    if(m_currentMoveData != NULL){
       if(m_currentMoveData->isAttackMove()){
            color = colorRed;
        }
    }else if(clicked){
        color = colorYellow;
    }

    SetColor(color);
}

void Square::highlightOff(){
    m_highlightOn = false;

    setToBoardColor();
}

void Square::setToBoardColor(){
    setToBoardColor(colorBlack, colorWhite);
}


//Sets the color the Square should be on the board, i.e. white or black. Or if it is clicked, highlight the Square
void Square::setToBoardColor(sf::Color black, sf::Color white){
    if(m_highlightOn){ return; }

    if(GetType() == WHITE){
        SetColor(white);
    }else{
        SetColor(black);
    }

    invalidate();
}

Square::Type Square::GetType(){
    return m_type;
}

