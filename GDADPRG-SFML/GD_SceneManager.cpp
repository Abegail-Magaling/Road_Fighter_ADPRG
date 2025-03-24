#include "GD_SceneManager.h"

GD_SceneManager* GD_SceneManager::myInstance = nullptr;

GD_SceneManager* GD_SceneManager::createInstance(){
    if(nullptr==myInstance)
        myInstance = new GD_SceneManager();
    return myInstance;
}

GD_SceneManager::GD_SceneManager(){
    currentScene = nullptr;
}

GD_SceneManager::~GD_SceneManager(){ 
    for(GD_Scene* s: scenes)
        delete s;
}

GD_Scene* GD_SceneManager::findScene(std::string name){
    for(GD_Scene* s: scenes){
        if(s->getName()==name)
            return s;
    }//end for
    return nullptr;
}

void GD_SceneManager::registerScene(GD_Scene* scene){
    scenes.push_back(scene);
}

GD_Scene* GD_SceneManager::loadScene(std::string id){
    if(nullptr!=currentScene && currentScene->getName() == id)
        return currentScene;
    
    GD_Scene* newCurrentScene = findScene(id);
    if(nullptr!=currentScene)
        currentScene->onUnload();
    newCurrentScene->onLoad();
    currentScene = newCurrentScene;
    return newCurrentScene;
}

GD_Scene* GD_SceneManager::getCurrentScene(){
    return currentScene;
}

void GD_SceneManager::updateCurrentScene(sf::Time deltaTime){
    if(nullptr!=currentScene)
        currentScene->update(deltaTime);
}

void GD_SceneManager::drawCurrentScene(sf::RenderWindow *window){
    if(nullptr!=currentScene)
        currentScene->draw(window);
}


