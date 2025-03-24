#include "GD_2DBlockObject.h"

GD_2DBlockObject::GD_2DBlockObject(std::string objName, std::string textureName, float tileSize):
        GD_GameObject(objName){
    GD_GameResource* res = GD_GameResource::createInstance();
    sf::IntRect rect = (*res->getAtlas())[textureName];
    sprite = new sf::Sprite(*res->getTexture(),rect);
    
    sprite->setOrigin({rect.size.x/2.f, rect.size.y/2.f});
    sprite->setScale({tileSize/rect.size.x, tileSize/rect.size.y});
    sprite->move({tileSize/2, tileSize/2});
    
    tileSideSize = tileSize;
    x = 0;
    y = 0;
    visible = true;
}

GD_2DBlockObject::~GD_2DBlockObject(){
    delete sprite;
}

void GD_2DBlockObject::init(){}
void GD_2DBlockObject::update(sf::Time deltaTime){}

void GD_2DBlockObject::draw(sf::RenderWindow *window){
    window->draw(*sprite);
}

void GD_2DBlockObject::setParent(GD_2DBlockObject* parentVal){
    parent = parentVal;
    //return &this;
}
        
void GD_2DBlockObject::attachChild(GD_2DBlockObject* child){
    children.push_back(child);
    child->setParent(this);    
}

std::vector<GD_2DBlockObject*> GD_2DBlockObject::getAllChildren(){
    return children;
}

bool GD_2DBlockObject::isVisible(){ return visible; }
void GD_2DBlockObject::toggleVisibility(){ visible = !visible; }
sf::Sprite* GD_2DBlockObject::getSprite(){ return sprite; }

GD_2DBlockObject* GD_2DBlockObject::getParent(){
    return parent;
}

GD_2DBlockObject* GD_2DBlockObject::getChild(std::string objName){
    for(GD_2DBlockObject* child: children)
        if(child->getName() == objName)
            return child;
    return nullptr;
}

void GD_2DBlockObject::setTileXY(int xV, int yV){
    x = xV; y = yV;
    sprite->setPosition({tileSideSize*(x+0.5f), tileSideSize*(y+0.5f)});
}

int GD_2DBlockObject::getTileX(){ return x; }
int GD_2DBlockObject::getTileY(){ return y; }

float GD_2DBlockObject::getTileSize(){
    return tileSideSize;
}


