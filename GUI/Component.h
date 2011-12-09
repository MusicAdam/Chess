#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../State.h"

class Component: public sf::Shape
{
    public:

        Component();
        virtual ~Component();

        void draw();

        void SetSize(float w, float h);
        void SetSize(sf::Vector2f size);

        void SetColor(sf::Color newColor);
        sf::Color GetOutlineColor();
        void SetOutlineColor(sf::Color newColor);

        float           GetWidth();
        float           GetHeight();
        sf::Vector2f    GetSize();
        void performLayout();

        bool isValid();
        void invalidate();
    protected:
        void validate();

        bool shouldDraw();
        bool shouldLayout();
    private:
        bool m_shouldDraw;    //True when the compenent needs to be drawn
        bool m_shouldLayout;  //True when the compenent's size has changed
        bool m_valid;

        float m_width, m_height;

        sf::Color m_componentColor;
        sf::Color m_outlineColor;
        sf::Shape m_background;

        void think(State::type parentState);

};

#endif // COMPONENT_H
