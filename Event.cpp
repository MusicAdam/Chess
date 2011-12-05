#include "Event.h"
#include "RenderHandler.h"
#include "AI.h"

Event::Data::Data()
{
}

Event::Data::~Data()
{
    //dtor
}
/*
int Event::Data::setType(const int& type){
    m_type = type;
}

int Event::Data::type(){
    return m_type;
}

void Event::Data::setCallback(Event::Data::callBack functionPtr){
    m_callback  =   functionPtr;
}

Event::Data::callBack Event::Data::getCallback(){
    return m_callback;
}

*/
Event::Handler::Handler()
{
    stackHead = 0;

   // m_inputListener   =   &input;
}

Event::Handler::~Handler()
{
    //dtor
}
/*
void Event::Handler::addListener(const int& type, Data::callBack functionPtr){
    Event::Data newData;

    eventStack* newEvent = new eventStack;

    newData.setCallback(functionPtr);
    newData.setType(type);

    newEvent->data = newData;
    newEvent->next = NULL;

    if(stackHead == NULL){
        stackHead = newEvent;
    }else{

        eventStack* eventPointer;
        eventPointer = stackHead;

        while(eventPointer->next != NULL){
            eventPointer = eventPointer->next;
        }

        eventPointer->next = newEvent;
    }
}
*/
void Event::Handler::call(const int& type, sf::RenderWindow& App)
{
    eventStack* eventPointer;

    eventPointer = stackHead;
    /*
    while(eventPointer != NULL){
        int checkType = eventPointer->data.type();

        if(checkType == type){
            //Event::Data::callBack funcPtr = eventPointer->data.getCallback();

            //(*Board::funcPtr)(); //So wrong
        }

        eventPointer = eventPointer->next;
    }*/
}

void Event::Handler::listen(){
    sf::Event Event;
    sf::RenderWindow* Window = RenderHandler::Window();
    Board* Board = Board::Get();

    const sf::Input& Input = Window->GetInput();

    if((Window->GetEvent(Event)) == false) return;

    do{
        if(Event.Type == sf::Event::KeyReleased){
            if(Event.Key.Code == sf::Key::Escape){
                Window->Close();
            }

            if(Event.Key.Code == sf::Key::Space){
                if(Board->getState() == Board::STATE_NULL){
                    //Let the board know we want it to load now..
                    Board->setState(Board::STATE_LOADING);
                }else if(Board->getState() == Board::STATE_PLAY){
                    Board->spacePressed();
                }
            }

            if(Event.Key.Code == sf::Key::X){
                if(Board->getState() == Board::STATE_PLAY){
                    //Let the board know we want it to load now..
                    Board->setState(Board::STATE_EXIT);
                }
            }
        }

        // Close window : exit)
        if (Event.Type == sf::Event::Closed){
            Window->Close();
        }

        if((Event.Type == sf::Event::MouseButtonReleased)){
            if(Board->getState() == Board::STATE_PLAY){
                if(Event.MouseButton.Button == sf::Mouse::Left){
                    Board->Click(sf::Vector2f(Input.GetMouseX(), Input.GetMouseY()));
                }

                if(Event.MouseButton.Button == sf::Mouse::Right){
                    Board->outputClickData(Input.GetMouseX(), Input.GetMouseY());
                }
            }
        }


    }while(Window->GetEvent(Event));
}
