#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include "GUI/Component.h"

//Handles the updating of GUI compoentns

class RenderHandler
{
    public:
        struct renderComponents{Component* componentPointer; int index; int depth; renderComponents *next;};
        struct renderSprites{sf::Sprite* componentPointer; int index; int depth; renderSprites *next;};

        RenderHandler();
        ~RenderHandler();

        //Adds a component to the handler and returns the component index
        //For depth 0 is top higher number is lower
        int addComponent(Component &componentReference, int depth);
        int addComponent(Component &componentReference);

        //Set component by cmpIndex (component index) or by the component itself (sCmp)
        void setComponentDepth(int cmpIndex, int depth);
        void setComponentDepth(Component* sCmp, int depth);

        //DELETE THIS?
        int getMaxComponentDepth();

        bool isValid();
        void test();

        void render(sf::RenderWindow& App);
    protected:
    private:

        renderComponents*   cmpHead;
        renderSprites*      sprHead;

        //Returns the last renderObject
        renderComponents* scrollRenderComponents(Component* sCmp); //Scrolls to component
        renderComponents* scrollRenderComponents(); //Scrolls components
        renderComponents* scrollRenderSprites(sf::Sprite* sSpr); //Scrolls Sprites
        renderComponents* scrollRenderSprites(); //Scrolls to Sprite
        //Returns the number of objects in the list
        int getRenderListSize();

        void _setComponentDepth(renderComponents* stackPointer, int ndepth);
        void setDepthHighLow(int nd);

        int m_nextIndex;         //Index of the last element in the stacks
        int m_depthHigh, m_depthLow;
};

#endif // RenderHandler
