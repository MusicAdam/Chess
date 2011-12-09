#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>
#include "GUI/Component.h"
#include "ChessException.h"
#include "MoveData.h"

class Piece;

/*********************************************************
    Class:  Square
    What:   A class for Squares on a Board

    Note: inherits Component  to be drawable by Renderer
**********************************************************/

class Square: public Component
{
    public:
        enum Type{
            WHITE,
            BLACK
        };

        Square();
        ~Square();
        void setToBoardColor();
        void setToBoardColor(sf::Color black, sf::Color white);


        void setGridPos(int x, int y);
        void setGridPos(sf::Vector2i coord);
        int getGridX();
        int getGridY();
        sf::Vector2i getGridPos();
        void click();
        void PlacePiece(Piece* piece);
        /***********************************************
            sets current piece to null
        ***********************************************/
        void Empty();

        /***********************************************
            returns true if m_currentPiece is not null
        ***********************************************/
        bool Occupied();

        /***************
            Piece Getter

            Gets a piece by a unique index

            throws ChessException::NullPiece
        ****************/
        Piece* GetPiece() throw(ChessException);

        /***********************************************************************************************************
        "Creates a new  piece of a certain type”

        Name:       Square::CreatePiece( [bool should_return])
        What:       Push to m_pieces vector

        Return:		Piece //the new piece

        ******************
        ****PARAM LIST****
        +++++++++++++++++++++++++++++++++Type+++++Name+++++++++++++++Comment+++++++++++++++++++++++++++++++++++
        +    [Optional, default: true]   ::  bool    should_return         If true the new piece is returned

        ***************************************************************************************************************/
//        Piece* CreatePiece();


        Square::Type GetType();




        void highlightOff();
        void highlightOn();

        void outline(bool on);

        sf::Vector2f GetCenter();

        bool clicked;
        sf::Color colorBlack;
        sf::Color colorWhite;
        sf::Color colorGreen;
        sf::Color colorGreen_b;
        sf::Color colorRed;
        sf::Color colorYellow;

        int size;
        sf::Vector2i gridPos;
    protected:
    private:
        Piece*      m_currentPiece;      //Current Piece in the cell
        MoveData*   m_currentMoveData;   //Points to the current move data, is NULL if the Square is unaffected by the click

        bool            m_highlightOn; //true turns on highlight, false turns highlight off
        Square::Type    m_type;

        void setType();

};

#endif // Square_H
