#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"

class Board;

namespace Event {
const int MOUSE_RELEASE  =   0;
const int MOUSE_MOVE     =   1;

class Data
{
    public:
        typedef void (Board::*callBack)();

        Data();
        virtual ~Data();

        int type();
        void setCallback(callBack functionPtr);
        callBack getCallback();
        int setType(const int& type);
    protected:
        int m_type;
        callBack m_callback;
    private:

};

class Handler
{
    public:
        Handler();
        virtual ~Handler();

        void addListener(const int& type, Data::callBack f);
        void call(const int& type, sf::RenderWindow& App);
        //CAUTION: This function is called an undefined number of times while the app is open, keep its functionality light!!
        void listen(sf::RenderWindow& App);
    protected:
    private:
        struct eventStack {Event::Data data; eventStack* next;};
        eventStack  *stackHead;

        const sf::Input* m_inputListener;
};


};//Namespace


#endif // EVENT_H
