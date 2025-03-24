#include "GD_ModularObject.h"

GD_ModularObject::GD_ModularObject(std::string objName, 
        std::string textureName, float tileSize):
        GD_2DBlockObject(objName,textureName,tileSize){
}

GD_ModularObject::~GD_ModularObject(){
    for(GD_Component* cmp: componentList)
        delete cmp;
}

void GD_ModularObject::attachComponent(GD_Component* component){
    componentList.push_back(component);
    component->attachOwner(this);
}

GD_Component* GD_ModularObject::getComponent(std::string componentName){
    for(GD_Component* cmp: componentList)
        if(cmp->getName() == componentName)
            return cmp;
    return nullptr;
}

void GD_ModularObject::update(sf::Time deltaTime){
    for(GD_2DBlockObject* child: getAllChildren())
        child->update(deltaTime);
    for(GD_Component* cmp: componentList)
        cmp->perform(deltaTime);
}
