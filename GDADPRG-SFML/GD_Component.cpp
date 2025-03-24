#include "GD_Component.h"

GD_Component::GD_Component(std::string name){
    this->name = name;
}

void GD_Component::attachOwner(GD_ModularObject* owner){
    this->owner = owner;
}

GD_ModularObject* GD_Component::getOwner(){ 
    return owner;
}

std::string GD_Component::getName(){
    return name;
}
