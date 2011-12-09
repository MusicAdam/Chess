#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

#include "Event.h"
#include "Square.h"
#include "Rules.h"
#include "RenderHandler.h"
#include "TileMap.h"

class Piece;

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

        ~Board();


        bool Click(sf::Vector2f mCoord);
        Piece* GetPiece(int i);

        void setState(const int nstate);
        const int getState();

        void performAction(Square* clickedSquare);

        int ActivePlayer();

        void DebugClick(sf::Vector2f mCoord);
        void DebugPreviousSelection(sf::Vector2f mCoord);

        //Loads the board
        bool load();
        void unload();

        void think();

        bool IsLoaded();
        void Deselect();

void outputClickData(int mouseX, int mouseY);

        void spacePressed();
        void highlightSquare(int x, int y, bool moveType);
        void hideSquareHighlight(int x, int y);

        void killPiece(int index);

        static Board* Get(bool init);
        static Board* Get();

        float X;
        float Y;
        int height;
        int width;
        sf::Vector2i selectedSquare;
    protected:
        Board();
    private:

        static Board* BoardPtr;

        //Removes all pieces and Squares
        //void unload();
        //Deletes the board
        void exit();
        //Initialize the pieces array
        void createPieces();
        //Initialize Squares array
        //void createSquares();
        void turn();

        Piece pieces[32];
        float screenWidth;
        float screenHeight;
        Piece* m_selectedPiece;
        int m_clickedPiece;
        int m_state;
        int m_activePlayer; //The player id whose turn it is
        int m_actionPerformed; //True if an action was performed on this turn

        //Loading flags
        bool m_isLoaded; //True when all of the Board's resources and data have been loaded
};

#endif // BOARD_H
