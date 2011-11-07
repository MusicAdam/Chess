#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Cell.h"
#include "GamePiece.h"
#include "Chess.h"

#include "Event.h"
#include "RenderHandler.h"
#include "GUI/Component.h"
#include "GUI/Container.h"

#include <cmath>

using namespace std;

//Updates the render window (intelligently)
void update(sf::RenderWindow &App, Board &gameBoard);

void testFunc(){
    std::cout << "Hello world!\n";
}

int main()
{


    // Create the main rendering window
    sf::RenderWindow App(sf::VideoMode::GetMode(3), "Chess - Adam Zielinski"); //sf::Style::Fullscreen

    Event::Handler EventHandler;
    RenderHandler RenderHandler;

    Board gameBoard(App, RenderHandler);

   /* void (Board::*memPtr)();
    memPtr = &Board::clickCell;

    EventHandler.addListener(Event::MOUSE_RELEASE, memPtr);
    EventHandler.call(Event::MOUSE_RELEASE, App);
*/
    while (App.IsOpened())
    {

        EventHandler.listen(App);

        // Clear screen


        /*if(!gameBoard.isValid()){
            App.Clear(sf::Color(100, 100, 100));
            update(App, gameBoard);
            App.Display();
        }*/



        if(!RenderHandler.isValid()){
            RenderHandler.render(App);
        }
    }

    return EXIT_SUCCESS;
}

void update(sf::RenderWindow &App, Board &gameBoard) {
    std::cout << "Draw\n\n";

    /* MOVE TO FRAME */

    sf::Font MyFont;

    // Load from a font file on disk
    if (!MyFont.LoadFromFile("tahoma.ttf"))
    {
        // Error...
    }

    sf::String Player1Title;
    Player1Title.SetText("Player 1");
    Player1Title.SetSize(20);
    Player1Title.SetColor(sf::Color(255, 255, 255));
    Player1Title.SetPosition(gameBoard.X - 200, gameBoard.Y);

    App.Draw(Player1Title);

    sf::String Player2Title;
    Player2Title.SetText("Player 2");
    Player2Title.SetSize(20);
    Player2Title.SetColor(sf::Color(255, 255, 255));
    Player2Title.SetPosition((gameBoard.X + gameBoard.width)+(200-(Player2Title.GetSize()*8)) , gameBoard.Y);

    App.Draw(Player2Title);

    /* --- */


    Cell important;

    //Draw Board
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            Cell cell = gameBoard.getCell(i, j);

            if(cell.important){
                important = cell;
            }else{
                App.Draw(cell);
            }

        }
    }

    App.Draw(important);

    Rules Rules;
    sf::Image pawnImage;
    pawnImage.LoadFromFile("pawn.png");
    sf::Image rookImage;
    rookImage.LoadFromFile("rook.png");
    sf::Image knight;
    knight.LoadFromFile("knight.png");
    sf::Image bishop;
    bishop.LoadFromFile("bishop.png");
    sf::Image queen;
    queen.LoadFromFile("queen.png");
    sf::Image king;
    king.LoadFromFile("king.png");

    //Draw pawns to board
    for(int i=0; i<32 ; i++){
        GamePiece piece = gameBoard.getGamePiece(i);
        switch(piece.getType()){
            case GamePiece::Pawn:
                piece.SetImage(pawnImage);
                break;
            case GamePiece::King:
                piece.SetImage(king);
                break;

            case GamePiece::Rook:
                piece.SetImage(rookImage);
                break;

            case GamePiece::Bishop:
                piece.SetImage(bishop);
                break;

            case GamePiece::Queen:
                piece.SetImage(queen);
                break;

            case GamePiece::Knight:
                piece.SetImage(knight);
                break;

        }

        App.Draw(piece);
    }

    gameBoard.validate();
}
