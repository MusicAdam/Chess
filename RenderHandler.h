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

        //Set component by cmpIndex (component index) or by the component itself (sCmp)
        void setComponentDepth(int cmpIndex, int depth);
        void setComponentDepth(Component* sCmp, int depth);

        int getMaxDepth();

        bool isValid();

        void render(sf::RenderWindow& App);
    protected:
    private:

        renderObject* head;

        //Returns the last renderObject
        renderObject* scrollRenderObjects(int cur);
        renderObject* scrollRenderObjects(Component* sCmp);
        renderObject* scrollRenderObjects();
        //Returns the number of objects in the list
        int getRenderListSize();

        void _setComponentDepth(renderObject* stackPointer, int ndepth);
        void setDepthHighLow(int nd);

        int m_nextIndex;         //Index of the last element in the stacks
        int m_depthHigh, m_depthLow;
};

#endif // RenderHandler
