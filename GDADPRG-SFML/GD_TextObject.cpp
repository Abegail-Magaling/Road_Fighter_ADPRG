#include "GD_TextObject.h"

GD_TextObject::GD_TextObject(std::string id,std::string text,float x,float y):
        GD_GameObject(id){
    GD_GameResource* res = GD_GameResource::createInstance();
    textObject = new sf::Text(*res->getFont());
    textObject->setString(text);
    textObject->setFillColor(sf::Color::White);
    textObject->setPosition({x,y});
}

GD_TextObject::~GD_TextObject(){
    delete textObject;
}

void GD_TextObject::setText(std::string text){
    textObject->setString(text);
}

void GD_TextObject::move(float x,float y){
    textObject->setPosition({x,y});
}

void GD_TextObject::init(){}

void GD_TextObject::update(sf::Time deltaTime){}

void GD_TextObject::draw(sf::RenderWindow *window){
    window->draw(*textObject);
}
