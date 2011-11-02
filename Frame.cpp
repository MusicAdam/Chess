#include "Frame.h"

Frame::Frame()
{

}

/*  -VALIDATES FRAME
    -OVERWRITABLE
    Adds all the points with the width, height and color information.

    Should be called when invalid.
*/
/*
void Frame::draw()
{

}

/* INVLAIDATES FRAME
    setBackgroundColor(sf::Color);

    Sets the background color of the board
*/
/*
void Frame::setBackgroundColor(sf::Color newColor)
{

}

/* INVLAIDATES FRAME
    setTitleColor(sf::Color);

    Sets the background color of the board
*/
/*
void Frame::setTitleColor(sf::Color newColor)
{

}

/* INVLAIDATES FRAME
    setText(sf::String);

    Sets the title text
*/
/*
void Frame::setText(sf::String newText){

}

/* INVLAIDATES FRAME
    Set the size of the frame
*/
/*
void Frame::setSize(sf::Vector2f size){
    width = size.x;
    height = size.y;

    invalidate();
}

/* INVLAIDATES FRAME
    Set the size of the frame
*/
/*
void Frame::setSize(float newWidth, float newHeight){
    sf::Vector2f tempVect;
    tempVect.x = newWidth;
    tempVect.y = newHeight;

    setSize(tempVect);
}

/*
    Forces the Frame to be drawn
*/
/*
void Frame::invalidate(){
    valid = false;
    needsDraw = true;
}


/*
    If local drawing updates have been made, let the heirarchy know that this frame is now valid
*/
/*
void Frame::validate(){
    if(!needsDraw){
        valid = true;
    }
}
*/
