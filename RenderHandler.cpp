#include "RenderHandler.h"

RenderHandler::RenderHandler()
{
    cmpHead         =   NULL;
    sprHead         =   NULL;
    m_nextIndex     =   0;
    m_depthHigh     =   0;
    m_depthLow      =   0;
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
}


int RenderHandler::addComponent(Component& componentReference, int depth){
    renderComponents* componentPtr = new renderComponents;
    Component* newComponent =   &componentReference;
    renderComponents* scrollPtr;

    //Component* newComponent =   dynamic_cast<Component*> (componentReference);

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
    return m_nextIndex++;
}

int RenderHandler::addComponent(Component &componentReference)
{
    int index = addComponent(componentReference, 0);

    return index;
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
bool RenderHandler::isValid(){
    renderComponents* currentPointer;
    currentPointer = cmpHead;

    bool returnValid = true;

    while(currentPointer != NULL){
        if(!currentPointer->componentPointer->isValid()){
            returnValid = false;
            break;
        }

        currentPointer = currentPointer->next;
    }

    return returnValid;


}

void RenderHandler::render(sf::RenderWindow& App){
    renderComponents* currentPointer;
    currentPointer = cmpHead;

    App.Clear(sf::Color(100, 100, 100));


    while(currentPointer != NULL){
        if(!currentPointer->componentPointer->isValid()){
            currentPointer->componentPointer->draw(App);
            currentPointer = currentPointer->next;
        }
    }

    App.Display();
}


//Returns the last !NULL renderObject
//If scrollTo is set scrollRenderObjects will return the object with the given index
//WARNING: This will return the last renderObject if the index is not found with no warning!!

RenderHandler::renderComponents* RenderHandler::scrollRenderComponents(Component* toCmp){
    renderComponents* currentPointer;
    currentPointer = cmpHead;

    while(currentPointer->next != NULL){
        std::cout << "Here\n";
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

    std::cout << "Scrolling list:\n";
    while(currentPointer != NULL){
        std::cout << "\t[" << currentPointer->index << "]Depth: " << currentPointer->depth << std::endl;
        std::cout << "\t\tNext = " << currentPointer->next << std::endl;
        currentPointer = currentPointer->next;
    }

    std::cout << "\n\nLIST TEST ENDED\n\n";
}
