#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include <SFML/Graphics.hpp>

class Component;


/*
    In the future, change to template structure so there is no need for two separate addComponent Functions
*/

//Handles the updating of GUI compoentns
class RenderHandler
{
    public:
        struct renderComponents{Component* componentPointer; int index; int depth; renderComponents *next;};
        struct renderSprites{sf::Sprite* spritePointer; int index; int depth; renderSprites *next;};

        ~RenderHandler();

        static RenderHandler* Get();
        static sf::RenderWindow* Window();

        //Adds a component to the handler and returns the component index
        //For depth 0 is top higher number is lower
        int addComponent(Component &componentReference, int depth);
        int addComponent(Component &componentReference);
        int addComponent(sf::Sprite &spriteReference, int depth);
        int addComponent(sf::Sprite &spriteReference);

        void removeComponent(Component* cmpPtr);
        void removeComponent(sf::Sprite* sprPtr);

        //Set component by cmpIndex (component index) or by the component itself (sCmp)
        void setComponentDepth(int cmpIndex, int depth);
        void setComponentDepth(Component* sCmp, int depth);

        //DELETE THIS?
        int getMaxComponentDepth();

        bool isValid();
        //Force the board to redraw
        void invalidate();

        void test();

        void render();
    protected:
        RenderHandler();
    private:
        static RenderHandler*       RenderHandlerPtr;
        static sf::RenderWindow*    WindowPtr;

        renderComponents*   cmpHead;
        renderSprites*      sprHead;

        //Returns the last renderObject
        renderComponents* scrollRenderComponents(Component* sCmp); //Scrolls to component
        renderComponents* scrollRenderComponents(); //Scrolls components
        renderComponents* scrollRenderSprites(sf::Sprite* sSpr); //Scrolls Sprites
        renderComponents* scrollRenderSprites(); //Scrolls to Sprite
        //Returns the number of objects in the list
        int getRenderListSize();
        void validate();

        void _setComponentDepth(renderComponents* stackPointer, int ndepth);
        void setDepthHighLow(int nd);

        int m_nextIndex;         //Index of the last element in the stacks
        int m_depthHigh, m_depthLow;
        int m_sprCount, m_cmpCount;
        bool m_isValid;
};

#endif // RenderHandler
