#include "RenderHandler.h"
#include "GUI/Component.h"
//#include "Chess.h"

RenderHandler*       RenderHandler::RenderHandlerPtr = NULL;
sf::RenderWindow*    RenderHandler::WindowPtr        = NULL;

RenderHandler::RenderHandler()
{
    cmpHead         =   NULL;
    sprHead         =   NULL;
    m_nextIndex     =   0;
    m_depthHigh     =   0;
    m_depthLow      =   0;
    m_cmpCount      =   0;
    m_sprCount      =   0;
    m_isValid       =   false;
}

//Clean up all the allocated memory space
RenderHandler::~RenderHandler()
{
    //Clean components
    renderComponents*   componentPtr;
    renderComponents*   tmp_next;

    componentPtr = cmpHead;

    while(componentPtr != NULL){
        tmp_next        = componentPtr->next;
        delete [] componentPtr;
        componentPtr  = tmp_next;
    }

    delete [] tmp_next;

    //Clean sprites
    renderSprites*   sprPtr;
    renderSprites*   tmp_next2;

    sprPtr = sprHead;

    while(sprPtr != NULL){
        tmp_next2        = sprPtr->next;
        delete [] sprPtr;
        sprPtr  = tmp_next2;
    }

    delete [] tmp_next2;
    delete []  WindowPtr;
    delete [] RenderHandlerPtr;
}

static sf::RenderWindow* RenderHandler::Window(){
    if(WindowPtr == NULL){
        WindowPtr = new sf::RenderWindow(sf::VideoMode::GetMode(3), "Chess - Adam Zielinski");
    }
    return WindowPtr;
}

static RenderHandler* RenderHandler::Get(){
    if(RenderHandlerPtr == NULL){
        RenderHandlerPtr = new RenderHandler();
    }

    return RenderHandlerPtr;
}


int RenderHandler::addComponent(Component& componentReference, int depth){
    renderComponents* componentPtr = new renderComponents;
    Component* newComponent =   &componentReference;

    renderComponents* scrollPtr;


    //Component* newComponent =   dynamic_cast<Component*> (&componentReference);

    //std::cout << "Adding component [" << m_nextIndex << "] at depth " << depth << std::endl;

    componentPtr->index                  =   m_nextIndex;//getRenderListSize();
    componentPtr->componentPointer       =   newComponent;
    componentPtr->depth                  =   depth;
    componentPtr->next                   =   NULL;

   // setDepthHighLow(depth);

    if(cmpHead== NULL){
        //std::cout << "head not set... adding component as head\n";
        cmpHead = componentPtr;
    }else{
        scrollPtr           = cmpHead;
        //std::cout << "Scrolling list..\n";

        if(depth > cmpHead->depth){
            //std::cout << "Inserting at beginning of list...\nSetting new pointer's next to the list\n";
            //renderObjectPointer->next = cmpHead ;
            //std::cout << "Good...\nSetting head to the new structure\n";
            cmpHead = componentPtr;
           // std::cout << "Good\n";
        }else{
            while(scrollPtr!=NULL){
                if(scrollPtr->next == NULL){
                    break;
                }

                if(depth > (scrollPtr->next->depth)){
               //    std::cout << "TRUE\n\tExiting...\n";
                    break;
               }else{
             //      std::cout << "FALSE\n";
               }

                scrollPtr = scrollPtr->next;

            }

            //std::cout << "Setting new pointer's next to the current lists next... " << scrollPtr->next << " ";
            componentPtr->next = scrollPtr->next;
            //std::cout << "Good.\nSetting curent lists next to the new pointer... ";
            scrollPtr->next = componentPtr;
           // std::cout << "Good\nSetting head to the new structure";
            //std::cout << "Good\n";
        }
    }


    //std::cout << "Component added successfully!\n\n";
    m_cmpCount++;
    return m_nextIndex++;
}

void RenderHandler::removeComponent(Component* cmpPtr){
    renderComponents* toRemove;
    renderComponents* scrollPtr;

    if(cmpPtr == cmpHead->componentPointer){
        toRemove = cmpHead;
        cmpHead = cmpHead->next;
    }else{
        scrollPtr = cmpHead;

        while(scrollPtr != NULL){
            if(scrollPtr->next->componentPointer == cmpPtr){
                toRemove = scrollPtr->next;
                break;
            }

            scrollPtr = scrollPtr->next;
        }

        scrollPtr->next = toRemove->next;
    }

    delete [] toRemove;
    m_cmpCount--;

    if(m_cmpCount == 0){
        cmpHead = NULL;
    }
}

void RenderHandler::removeComponent(sf::Sprite* sprPtr){
    renderSprites* toRemove;
    renderSprites* scrollPtr;

    if(sprPtr == sprHead->spritePointer){
        toRemove = sprHead;
        sprHead = sprHead->next;
    }else{
        scrollPtr = sprHead;

        while(scrollPtr != NULL){
            if(scrollPtr->next->spritePointer == sprPtr){
                toRemove = scrollPtr->next;
                break;
            }

            scrollPtr = scrollPtr->next;
        }

        scrollPtr->next = toRemove->next;
    }

    delete [] toRemove;
    m_sprCount--;

    if(m_sprCount == 0){
        sprHead = NULL;
    }
}

int RenderHandler::addComponent(Component &componentReference)
{
    int index = addComponent(componentReference, 0);

    return index;
}

int RenderHandler::addComponent(sf::Sprite &sprRef, int depth)
{
    renderSprites* spritePtr = new renderSprites;
    sf::Sprite* newSprite =   &sprRef;

    renderSprites* scrollPtr;


    //Component* newComponent =   dynamic_cast<Component*> (&componentReference);

    //std::cout << "Adding component [" << m_nextIndex << "] at depth " << depth << std::endl;

    spritePtr->index                  =   m_nextIndex;//getRenderListSize();
    spritePtr->spritePointer          =   newSprite;
    spritePtr->depth                  =   depth;
    spritePtr->next                   =   NULL;

   // setDepthHighLow(depth);

    if(sprHead== NULL){
        //std::cout << "head not set... adding component as head\n";
        sprHead = spritePtr;
    }else{
        scrollPtr           = sprHead;
        //std::cout << "Scrolling list..\n";

        if(depth > sprHead->depth){
            //std::cout << "Inserting at beginning of list...\nSetting new pointer's next to the list\n";
            //renderObjectPointer->next = cmpHead ;
            //std::cout << "Good...\nSetting head to the new structure\n";
            sprHead = spritePtr;
           // std::cout << "Good\n";
        }else{
            while(scrollPtr!=NULL){
                if(scrollPtr->next == NULL){
                    break;
                }

                if(depth > (scrollPtr->next->depth)){
               //    std::cout << "TRUE\n\tExiting...\n";
                    break;
               }else{
             //      std::cout << "FALSE\n";
               }

                scrollPtr = scrollPtr->next;

            }

            //std::cout << "Setting new pointer's next to the current lists next... " << scrollPtr->next << " ";
            spritePtr->next = scrollPtr->next;
            //std::cout << "Good.\nSetting curent lists next to the new pointer... ";
            scrollPtr->next = spritePtr;
           // std::cout << "Good\nSetting head to the new structure";
            //std::cout << "Good\n";
        }
    }


    //std::cout << "Component added successfully!\n\n";
    m_sprCount++;
    return m_nextIndex++;
}

int RenderHandler::addComponent(sf::Sprite &sprRef)
{
    return addComponent(sprRef, 0);
}


//Should keep?
int RenderHandler::getMaxComponentDepth(){
    renderComponents* currentPointer;
    currentPointer = cmpHead;

    int maxDepth=0;

    while(currentPointer != NULL){
        if(currentPointer->depth > maxDepth){
            maxDepth    =   currentPointer->depth;
        }

        currentPointer = currentPointer->next;
    }

    return maxDepth;
}

//Change this so that the component reports to the handler whether or not it is valid
//Validates the board if it is valid (sets m_isValid to true)
bool RenderHandler::isValid(){
    return m_isValid;
}

void RenderHandler::validate(){
    if(isValid()) return;

    renderComponents* cmpPointer;
    cmpPointer = cmpHead;

    while(cmpPointer != NULL){
        if(!cmpPointer->componentPointer->isValid()){
            return;
        }

        cmpPointer = cmpPointer->next;
    }

    m_isValid = true;
}

void RenderHandler::invalidate(){
    if(!m_isValid) return;
    m_isValid = false;
}

void RenderHandler::render(){
    sf::RenderWindow* Window = RenderHandler::Window();
    renderComponents* cmpPtr;
    cmpPtr = cmpHead;

    renderSprites* sprPtr;
    sprPtr = sprHead;

    Window->Clear(sf::Color(100, 100, 100));

    while(cmpPtr != NULL){
        cmpPtr->componentPointer->draw();

        cmpPtr = cmpPtr->next;
    }

    while(sprPtr != NULL){
        Window->Draw(*sprPtr->spritePointer);

        sprPtr = sprPtr->next;
    }

    Window->Display();

    validate();
}


//Returns the last !NULL renderObject
//If scrollTo is set scrollRenderObjects will return the object with the given index
//WARNING: This will return the last renderObject if the index is not found with no warning!!

RenderHandler::renderComponents* RenderHandler::scrollRenderComponents(Component* toCmp){
    renderComponents* currentPointer;
    currentPointer = cmpHead;

    while(currentPointer->next != NULL){
        if(currentPointer->componentPointer == toCmp){
            return currentPointer;
        }

        currentPointer = currentPointer->next;
    }

    std::cout << "****WARNING: scrollRenderObjects(): Requested component was not found, returning last component in list\n";


    return currentPointer;
}

RenderHandler::renderComponents* RenderHandler::scrollRenderComponents(){
    renderComponents* componentPtr;
    componentPtr = cmpHead;

    while(componentPtr->next != NULL){
        componentPtr = componentPtr->next;
    }

    return componentPtr;
}

void RenderHandler::_setComponentDepth(renderComponents* stackPointer, int ndepth){
    stackPointer->depth = ndepth;
}

void RenderHandler::setComponentDepth(Component* sCmp, int depth){
    renderComponents* stackPtr  = scrollRenderComponents(sCmp);

    _setComponentDepth(stackPtr, depth);
}

void RenderHandler::setDepthHighLow(int newDepth){
    if(newDepth > m_depthHigh){
        m_depthHigh = newDepth;
    }else if(newDepth < m_depthLow){
        m_depthLow  =   newDepth;
    }
}

void RenderHandler::test(){
    std::cout << "\n\nTESTING LIST INTEGRITY\n\n";
    std::cout << "\nCurrent m_nextIndex = " << m_nextIndex << std::endl;

    renderComponents* currentPointer;
    currentPointer =cmpHead;

    std::cout << "Scrolling list (" << m_cmpCount << "):\n";
    while(currentPointer != NULL){
        std::cout << "\t[" << currentPointer->index << "]Depth: " << currentPointer->depth << std::endl;
        std::cout << "\t\tNext = " << currentPointer->next << std::endl;
        currentPointer = currentPointer->next;
    }

    std::cout << "\n\nLIST TEST ENDED\n\n";
}
