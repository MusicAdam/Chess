#ifndef TEXT_H
#define TEXT_H

#include "Component.h"

class Text : public Component
{
    public:
        Text();
        virtual ~Text();

        //Gets the sf string so we can edit it
        //sf::String& Content();
    protected:
    private:
        sf::String content;
};

#endif // TEXT_H
