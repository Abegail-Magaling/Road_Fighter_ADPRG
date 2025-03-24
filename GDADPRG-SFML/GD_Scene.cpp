#include "GD_Scene.h"

GD_Scene::GD_Scene(std::string name){
    this->name=name;
}

GD_Scene::~GD_Scene(){
    for(GD_GameObject* obj: objects)
        delete obj;
}

std::string GD_Scene::getName(){
    return name;
}
        
void GD_Scene::update(sf::Time deltaTime){
    for(GD_GameObject* obj: objects)
        if(dynamic_cast<GD_ModularObject*>(obj) == nullptr ||
                (dynamic_cast<GD_ModularObject*>(obj) != nullptr 
                && ((GD_ModularObject*)obj)->isVisible()) )
            obj->update(deltaTime);
}

void GD_Scene::draw(sf::RenderWindow* window){
    for(GD_GameObject* obj: objects)
        if(dynamic_cast<GD_ModularObject*>(obj) == nullptr ||
                (dynamic_cast<GD_ModularObject*>(obj) != nullptr 
                && ((GD_ModularObject*)obj)->isVisible()) )
            obj->draw(window);
}
        
void GD_Scene::addObject(GD_GameObject* obj){
    objects.push_back(obj);
}

GD_GameObject* GD_Scene::findObject(std::string id){
    for(GD_GameObject* obj: objects)
        if(obj->getName() == id)
            return obj;
    return nullptr;
}
        
std::vector<GD_GameObject*> GD_Scene::getAllObjects(){
    return objects;
}

void GD_Scene::removeObject(std::string id){
    GD_GameObject* obj = findObject(id);
    removeObject(obj);
}

void GD_Scene::removeObject(GD_GameObject *obj){
    objects.erase(std::find(objects.begin(), objects.end(), obj));
}

void GD_Scene::removeAllObjects(){
    objects.clear();
}
