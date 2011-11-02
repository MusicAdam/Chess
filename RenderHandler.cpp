#include "RenderHandler.h"

RenderHandler::RenderHandler()
{
    head            =   NULL;
    m_maxDepth      =   0;
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
    //Component* newComponent =   dynamic_cast<Component*> (componentReference);
    int index = 0;

    //Set Depth
    if(depth == -1){
        depth = 0;//getMaxDepth();
    }

    renderObjectPointer->index                  =   index;//getRenderListSize();
    renderObjectPointer->componentPointer       =   newComponent;
    renderObjectPointer->depth                  =   depth;
    renderObjectPointer->next                   =   NULL;

    if(head == NULL){
        head = renderObjectPointer;
    }else{
        scrollRenderObjects()->next = renderObjectPointer;
    }

    return index;
}


int RenderHandler::addComponent(Component &componentReference)
{
    int index = addComponent(componentReference, 0);

    return index;
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

RenderHandler::renderObject* RenderHandler::scrollRenderObjects(){
    return scrollRenderObjects(-1);
}
//Returns the number of objects in the list
int getRenderListSize();
