#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Component: public sf::Shape
{
    public:

        Component();
        virtual ~Component();

        void draw();

        void setSize(float w, float h);
        void setSize(sf::Vector2f size);

        void setColor(sf::Color newColor);
        sf::Color getColor();
        void setOutlineColor(sf::Color newColor);
        sf::Color getOutlineColor();
        float getWidth();
        float getHeight();
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

};

#endif // COMPONENT_H
