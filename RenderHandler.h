#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include "GUI/Component.h"

//Handles the updating of GUI compoentns

class RenderHandler
{
    public:
        struct renderObject{Component* componentPointer; int index; int depth; renderObject *next;};

        RenderHandler();
        ~RenderHandler();

        //Adds a component to the handler and returns the component index
        //For depth 0 is top higher number is lower
        int addComponent(Component &componentReference, int depth);
        int addComponent(Component &componentReference);

        bool isValid();

        void render(sf::RenderWindow& App);
    protected:
    private:

        renderObject* head;

        //Returns the last renderObject
        renderObject* scrollRenderObjects(int cur);
        renderObject* scrollRenderObjects();
        //Returns the number of objects in the list
        int getRenderListSize();

        int m_maxDepth;         //The total depth (length) of the renderObject list
};

#endif // RenderHandler
