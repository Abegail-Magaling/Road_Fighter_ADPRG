#include "ACO_ColliderComp.h"

ACO_ColliderComp::ACO_ColliderComp(float tileSize):
        GD_Component("ACO_ColliderComp"){
    this->tileSize = tileSize;
}

void ACO_ColliderComp::perform(sf::Time deltaTime){}

float ACO_ColliderComp::getX(){
    GD_ModularObject* owner = getOwner();
    return owner->getSprite()->getPosition().x - tileSize/2;
}

float ACO_ColliderComp::getY(){
    GD_ModularObject* owner = getOwner();
    return owner->getSprite()->getPosition().y - tileSize/2;
}

float ACO_ColliderComp::getWidth(){
    GD_ModularObject* owner = getOwner();
    return owner->getSprite()->getScale().x * tileSize;
}

float ACO_ColliderComp::getHeight(){
    GD_ModularObject* owner = getOwner();
    return owner->getSprite()->getScale().y * tileSize;
}
