#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

#include "Event.h"
#include "Cell.h"
#include "Rules.h"
#include "ImageHandler.h"
#include "RenderHandler.h"
//


class GamePiece;

class Board
{
    public:

        enum Movement {
            /*
                MOVEMENT ACTIONS
                    The movement actions that can be performed by pieces
            */
            Move,       //Movement Action:  The standard cell to cell movement.
            Attack        //Movement Action:  Action when a cell is attacking.
        };

        typedef void (Board::*FuncPtr)();

        Board(sf::RenderWindow &App, RenderHandler &RenderHandler);
        Cell getCell(int i, int j);
        void clickCell(); //Event::Data e
        GamePiece getGamePiece(int i);
        void createPieces();
        void placePiece(int pIndex, int gX, int gY);
        int getSelectedCell();
        float calculateCellPosX(int gridX);
        bool canMovePiece(int pieceIndex, int clickedCellX, int clickedCellY, int moveType); //0 is movement, 1 is attack
        void jumpWithSelectedPiece(int x, int y);
        void selectCell(int x, int y);

        /*
            //If selected cell is set
        */
        bool cellIsSelected();

        /*
            //If specefied cell is selected
        */
        bool cellIsSelected(int x, int y);

        /*
            Calculate the x position of the cell relative to the window
        */
        float calculateCellPosY(int gridY);


        /*
            Gets the center of a cell relative to the window
        */
        const sf::Vector2f getCellCenter(int cellX, int cellY);

        /*
            Gets the cell position in pixels relative to the window
        */
        const sf::Vector2f calculateCellPos(int gridX, int gridY);

        /*
            Validates the board
        */
        void validate();

        /*
            Returns true when the board is valid (has been drawn)
        */
        bool isValid();

        /*
            Toggles selected cell the erases the selection
            INVALIDATES BOARD
        */
        void deselect();

        void moveSelectedPieceTo(int x, int y);

        void performAction(Cell& clickedCell, GamePiece&  clickedPiece);

        float X;
        float Y;
        int height;
        int width;
        sf::Vector2i selectedCell;
    protected:
    private:
        int getCellGridPosX(sf::RenderWindow &App, int mouseX, int mouseY);
        int getCellGridPosY(sf::RenderWindow &App, int mouseX, int mouseY);

        int cellSize;
        Cell cells[8][8];
        Cell nullCell;  //Used for selection when no other cell is selected
        GamePiece pieces[32];
        float screenWidth ;
        float screenHeight;
        void invalidate();

        bool valid;
};

#endif // BOARD_H
