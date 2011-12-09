#include "Component.h"
#include "../RenderHandler.h"

Component::Component()
{
    AddPoint(0, 0, GetColor());
    AddPoint(GetWidth(), 0, GetColor());
    AddPoint(GetWidth(), GetHeight(), GetColor());
    AddPoint(0, GetHeight(), GetColor());

    SetPosition(0, 0);
    SetColor(sf::Color(255, 255, 255)); //Default color
    SetOutlineColor(sf::Color(0, 0, 0));
    SetSize(100, 100); //Default size
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
    SetPointPosition(1, GetWidth(), 0);
    SetPointPosition(2, GetWidth(), GetHeight());
    SetPointPosition(3, 0, GetHeight());

    //Color
    for(int point=0; point<GetNbPoints(); point++){
        SetPointColor(point, GetColor());
        SetPointOutlineColor(point, GetOutlineColor());
    }

    //After layout is done
    m_shouldLayout = false;
}

/*
    public draw()
    Draws things to screen
*/
void Component::draw(){
    //if(shouldDraw()){ //Apparently SFML doesn't support the redrawing of individual elemtns and i "[should not] worry about that" (http://www.sfml-dev.org/forum/viewtopic.php?p=41329#41329)
        RenderHandler::Window()->Draw(*this);
        m_shouldDraw = false;

        //Attempt to validate:
        validate();
   // }
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

    RenderHandler::Get()->invalidate();
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
        //RenderHandler::Get()->validate();
    }else{
     //   std::cout << "Component is not valid\n\n";
    }
}


void Component::SetSize(float w, float h){
    m_width   =   w;
    m_height  =   h;

    invalidate();
}

void Component::SetSize(sf::Vector2f size){
    SetSize(size.x, size.y);
}

float Component::GetWidth(){ return m_width; }
float Component::GetHeight(){ return m_height; }
sf::Vector2f Component::GetSize(){ return sf::Vector2f(m_width, m_height); }


void Component::SetColor(sf::Color newColor){ sf::Shape::SetColor(newColor); invalidate(); }
void Component::SetOutlineColor(sf::Color newColor){m_outlineColor = newColor; invalidate(); }
sf::Color Component::GetOutlineColor(){ return m_outlineColor; }

bool Component::shouldDraw(){
    //std::cout << "\tbool Component::shouldDraw()\n\treturns " << m_shouldDraw << std::endl;
    return m_shouldDraw;//shouldD;
}

bool Component::shouldLayout(){ return m_shouldLayout; }
