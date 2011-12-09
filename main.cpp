#include <SFML/Graphics.hpp>
#include <iostream>

#include "RenderHandler.h"
#include "Event.h"
#include "Board.h"
#include "Player.h"


/*
    Should probably write a resource handler at some point....
*/

using std::cout;

int main()
{

    RenderHandler* RenderHandler    = RenderHandler::Get();
    sf::RenderWindow* Window        = RenderHandler::Window();
    Event::Handler EventHandler;

    /*
        This is here for now, but in the future it should be selectable by the user through the main menu
    */

    Player::One()->setController(Player::CONTROL_HUMAN);  //Player one is controlled by the human
    Player::Two()->setController(Player::CONTROL_AI);     //Player two is controlled by the AI

    while (Window->IsOpened())
    {
        EventHandler.listen();

        if(!RenderHandler->isValid()){
           RenderHandler->render();
        }


        Board::Get()->think();
        //RenderHandler->Think
    }


    return EXIT_SUCCESS;
}

