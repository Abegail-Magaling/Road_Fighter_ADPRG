#include "GD_GameObject.h"


GD_GameObject::GD_GameObject(std::string objName){
    name = objName;
}

std::string GD_GameObject::getName(){
    return name; 
}

