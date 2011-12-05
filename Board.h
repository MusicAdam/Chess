#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

#include "Event.h"
#include "Cell.h"
#include "Rules.h"
#include "RenderHandler.h"
#include "TileMap.h"

class GamePiece;

class Board : public TileMap
{
    public:

        enum {
            /*
                NIL - Game not loaded AKA player is still in main menu
                LOADING - Game is loading resources (images for sprites, creating the game board etc.)
                PLAY - Game is running
                STATE_TURN - Turns are switching
                PAUSE - Game is paused (player is in a menu)
                EXIT - Game is exiting and resources are being unloaded

            */

            STATE_NULL,
            STATE_LOADING,
            STATE_PLAY,
            STATE_TURN,
            STATE_PAUSE,
            STATE_EXIT
        };

        struct Exception{
            const int Move  =   0;
        };

        ~Board();


        bool Click(sf::Vector2f mCoord);
        GamePiece getGamePiece(int i);

        void placePieceInCell(int index, sf::Vector2i cell);
        void removePieceFromCell(sf::Vector2i cell);

        bool canMovePiece(int pieceIndex, int clickedCellX, int clickedCellY, int moveType); //0 is movement, 1 is attack
        void jumpWithSelectedPiece(int x, int y);
        void selectCell(int x, int y);

        void setState(const int nstate);
        const int getState();

        void moveSelectedPieceTo(int x, int y);

        void performAction(Cell& clickedCell);

        int ActivePlayer();

        //Loads the board
        bool load();

        void think();

        bool IsLoaded();

void outputClickData(int mouseX, int mouseY);

        void spacePressed();
        void highlightCell(int x, int y, bool moveType);
        void hideCellHighlight(int x, int y);

        void killPiece(int index);

        static Board* Get(bool init);
        static Board* Get();

        float X;
        float Y;
        int height;
        int width;
        sf::Vector2i selectedCell;
    protected:
        Board();
    private:

        static Board* BoardPtr;

        //Removes all pieces and cells
        //void unload();
        //Deletes the board
        void exit();
        //Initialize the pieces array
        void createPieces();
        //Initialize cells array
        //void createCells();
        void turn();

        GamePiece pieces[32];
        float screenWidth ;
        float screenHeight;
        int m_selectedPiece;
        int m_clickedPiece;
        int m_state;
        int m_activePlayer; //The player id whose turn it is
        int m_actionPerformed; //True if an action was performed on this turn

        //Loading flags
        bool m_isLoaded; //True when all of the Board's resources and data have been loaded
};

#endif // BOARD_H
