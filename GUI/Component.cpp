#include "Component.h"

Component::Component()
{
    AddPoint(0, 0, getColor());
    AddPoint(getWidth(), 0, getColor());
    AddPoint(getWidth(), getHeight(), getColor());
    AddPoint(0, getHeight(), getColor());

    SetPosition(0, 0);
    setColor(sf::Color(255, 255, 255)); //Default color
    setOutlineColor(sf::Color(0, 0, 0));
    setSize(100, 100); //Default size
}

Component::~Component()
{
    //dtor
}

/*
    perform layout
    repositions points
*/
void Component::performLayout(){
    if(!shouldLayout()) return;

    //Layout
    SetPointPosition(0, 0, 0);
    SetPointPosition(1, getWidth(), 0);
    SetPointPosition(2, getWidth(), getHeight());
    SetPointPosition(3, 0, getHeight());

    //Color
    for(int point=0; point<GetNbPoints(); point++){
        SetPointColor(point, getColor());
        SetPointOutlineColor(point, getOutlineColor());
    }

    //After layout is done
    m_shouldLayout = false;
}

/*
    public draw()
    Draws things to screen
*/
void Component::draw(sf::RenderWindow& Chess){
    if(shouldDraw()){
        Chess.Draw(*this);
        m_shouldDraw = false;

        //Attempt to validate:
        validate();
    }
}


/*
    public isValid()
    Returns true if the component is valid
*/
bool Component::isValid(){
    return m_valid;
}

/*
    protected invalidate() FORCES DRAW
    Invalidates the component
    FORCES DRAW
*/
void Component::invalidate(){
    m_shouldDraw            = true;
    m_shouldLayout          = true;
    m_valid                 = false;

    performLayout();
}

/*
    protected validate()
    Validates the component
*/
void Component::validate(){
   // std::cout << "Check component validity....\n";
    if(!shouldDraw() && !shouldLayout()){
        //std::cout << "Component is valid\n\n";
        m_valid = true;
    }else{
     //   std::cout << "Component is not valid\n\n";
    }
}


void Component::setSize(float w, float h){
    m_width   =   w;
    m_height  =   h;

    invalidate();
}

void Component::setSize(sf::Vector2f size){
    setSize(size.x, size.y);
}

float Component::getWidth(){ return m_width; }
float Component::getHeight(){ return m_height; }


void Component::setColor(sf::Color newColor){ m_componentColor = newColor; invalidate(); }
sf::Color Component::getColor(){return m_componentColor;}
void Component::setOutlineColor(sf::Color newColor){m_outlineColor = newColor; invalidate(); }
sf::Color Component::getOutlineColor(){ return m_outlineColor; }

bool Component::shouldDraw(){
    //std::cout << "\tbool Component::shouldDraw()\n\treturns " << m_shouldDraw << std::endl;
    return m_shouldDraw;//shouldD;
}

bool Component::shouldLayout(){ return m_shouldLayout; }
