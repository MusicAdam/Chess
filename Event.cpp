#include "Event.h"

Event::Data::Data()
{
}

Event::Data::~Data()
{
    //dtor
}

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


Event::Handler::Handler()
{
    stackHead = 0;

   // m_inputListener   =   &input;
}

Event::Handler::~Handler()
{
    //dtor
}

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

void Event::Handler::call(const int& type, sf::RenderWindow& App)
{
    eventStack* eventPointer;

    eventPointer = stackHead;

    while(eventPointer != NULL){
        int checkType = eventPointer->data.type();

        if(checkType == type){
            Event::Data::callBack funcPtr = eventPointer->data.getCallback();

            (*Board::funcPtr)(); //So wrong
        }

        eventPointer = eventPointer->next;
    }
}

void Event::Handler::listen(sf::RenderWindow& App){
    sf::Event Event;

    const sf::Input& Input = App.GetInput();

    if((App.GetEvent(Event)) == false) return;

    do{
        if((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Escape)){
            App.Close();
        }

        // Close window : exit)
        if (Event.Type == sf::Event::Closed){
            App.Close();
        }

         if((Event.Type == sf::Event::MouseButtonReleased)){
            call(Event::MOUSE_RELEASE, App);
            /*if((Input.GetMouseX() >= gameBoard.X) && (Input.GetMouseY() >= gameBoard.Y) && (Input.GetMouseX() <= gameBoard.X+gameBoard.width) && (Input.GetMouseY() <= gameBoard.Y+gameBoard.height)  ){
                int mouseX = Input.GetMouseX();
                int mouseY = Input.GetMouseY();

                gameBoard.clickCell(App, mouseX, mouseY);
            }else{
                gameBoard.deselect();
            }*/
        }


    }while(App.GetEvent(Event));
}
