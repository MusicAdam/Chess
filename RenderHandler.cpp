#include "RenderHandler.h"

RenderHandler::RenderHandler()
{
    head            =   NULL;
    m_nextIndex     =   0;
    m_depthHigh     =   0;
    m_depthLow      =   0;
}

//Clean up all the allocated memory space
RenderHandler::~RenderHandler()
{
    renderObject*   currentPointer;
    renderObject*   tmp_next;
    currentPointer = head;

    while(currentPointer != NULL){
        tmp_next        = currentPointer->next;
        delete [] currentPointer;
        currentPointer  = tmp_next;
    }

    delete [] tmp_next;
}


int RenderHandler::addComponent(Component& componentReference, int depth){
    renderObject* renderObjectPointer = new renderObject;
    Component* newComponent =   &componentReference;
    renderObject* scrollPtr;

    int curDepth=0;
    //Component* newComponent =   dynamic_cast<Component*> (componentReference);


    renderObjectPointer->index                  =   m_nextIndex;//getRenderListSize();
    renderObjectPointer->componentPointer       =   newComponent;
    renderObjectPointer->depth                  =   depth;
    renderObjectPointer->next                   =   NULL;

    setDepthHighLow(depth);

    int currentDepth = m_depthLow;

    if(head == NULL){
        head = renderObjectPointer;
    }else{
        scrollPtr           = head;

        while(scrollPtr!=NULL){
           if(scrollPtr->depth != depth && scrollPtr->depth>depth){
               std::cout << "*!*" <<  scrollPtr << std::endl;
                break;
           }

            scrollPtr = scrollPtr->next;
        }

        std::cout << "***" <<  scrollPtr << std::endl;
        head->next = scrollPtr;
        //head->next = scrollPtr;
/*
        renderObject* tmp = scrollPtr->next;
        renderObjectPointer = tmp;
        scrollPtr->next = renderObjectPointer;*/
    }



    return m_nextIndex++;
}

int RenderHandler::addComponent(Component &componentReference)
{
    int index = addComponent(componentReference, 0);

    return index;
}

int RenderHandler::getMaxDepth(){
    renderObject* currentPointer;
    currentPointer = head;

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
    renderObject* currentPointer;
    currentPointer = head;

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
    renderObject* currentPointer;
    currentPointer = head;

    App.Clear(sf::Color(100, 100, 100));


    while(currentPointer != NULL){
        if(!currentPointer->componentPointer->isValid()){
            std::cout << "Depth: " << currentPointer->depth << std::endl;
            currentPointer->componentPointer->draw(App);
            currentPointer = currentPointer->next;
        }
    }

    App.Display();
}


//Returns the last !NULL renderObject
//If scrollTo is set scrollRenderObjects will return the object with the given index
//WARNING: This will return the last renderObject if the index is not found with no warning!!
RenderHandler::renderObject* RenderHandler::scrollRenderObjects(int scrollTo){
    renderObject* currentPointer;
    currentPointer = head;

    while(currentPointer->next != NULL){
        if(scrollTo != -1 && scrollTo == currentPointer->index){
            return currentPointer;
        }

        currentPointer = currentPointer->next;
    }

    if(scrollTo != -1){
        std::cout << "****WARNING: scrollRenderObjects(int "<<scrollTo<<"): Requested index was not found, last element is being returned. This may or may not be the element you were looking for...\n";
    }

    return currentPointer;
}

RenderHandler::renderObject* RenderHandler::scrollRenderObjects(Component* toCmp){
    renderObject* currentPointer;
    currentPointer = head;

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

RenderHandler::renderObject* RenderHandler::scrollRenderObjects(){
    return scrollRenderObjects(-1);
}

void RenderHandler::_setComponentDepth(renderObject* stackPointer, int ndepth){
        stackPointer->depth = ndepth;
}

void RenderHandler::setComponentDepth(int cmpIndex, int depth){
    renderObject* stackPtr  = scrollRenderObjects(cmpIndex);

    _setComponentDepth(stackPtr, depth);
}
void RenderHandler::setComponentDepth(Component* sCmp, int depth){
    renderObject* stackPtr  = scrollRenderObjects(sCmp);

    _setComponentDepth(stackPtr, depth);
}

void RenderHandler::setDepthHighLow(int newDepth){
    if(newDepth > m_depthHigh){
        m_depthHigh = newDepth;
    }else if(newDepth < m_depthLow){
        m_depthLow  =   newDepth;
    }
}
