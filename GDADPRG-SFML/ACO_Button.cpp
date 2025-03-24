#include "ACO_Button.h"

ACO_Button::ACO_Button(std::string name,std::string textVal):
    	GD_GameObject(name){
    selected = false;
    elapsedTime = sf::Time::Zero;
    blinkTime = 1.f;
    
    rec = new sf::RectangleShape();
    rec->setFillColor(sf::Color::White);
    rec->setOutlineColor(sf::Color::Black);
    rec->setOutlineThickness(5);
    if(font.openFromFile("OpenSans-Medium.ttf")){
        text = new sf::Text(font);
        text->setString(textVal);
        text->setFillColor(sf::Color::Black);
        text->setCharacterSize(40);
    }
}

ACO_Button::~ACO_Button(){
    delete rec;
    delete text;
}

void ACO_Button::init(){}
void ACO_Button::update(sf::Time deltaTime){
    if(!selected) return;
    elapsedTime += deltaTime;
    if(elapsedTime.asSeconds()>=blinkTime){
        elapsedTime = sf::Time::Zero;
        if(rec->getOutlineColor() == sf::Color::Yellow)
            rec->setOutlineColor(sf::Color::Black);
        else
            rec->setOutlineColor(sf::Color::Yellow);
    }
}

void ACO_Button::draw(sf::RenderWindow *window){
    window->draw(*rec);
    window->draw(*text);
}
		
void ACO_Button::setPosition(float x,float y){
    rec->setPosition({x,y});
    text->setPosition({x,y});
}
		
void ACO_Button::setSize(float width,float height){
    rec->setSize({width,height});
    sf::Vector2f pos = rec->getPosition();
    text->setPosition({pos.x+width*0.1f,pos.y});
}

void ACO_Button::setText(std::string value){
    text->setString(value);
}

void ACO_Button::setBlinkTime(float blinkTime){
    this->blinkTime=blinkTime;
}

void ACO_Button::toggleSelected(){ 
    selected = !selected;
	elapsedTime = sf::Time::Zero;
	if(selected) rec->setOutlineColor(sf::Color::Yellow);
	else rec->setOutlineColor(sf::Color::Black);
}

bool ACO_Button::isSelected(){
    return selected;
}

