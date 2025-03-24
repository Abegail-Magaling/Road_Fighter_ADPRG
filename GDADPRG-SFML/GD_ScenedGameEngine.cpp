#include "GD_ScenedGameEngine.h"

GD_ScenedGameEngine::~GD_ScenedGameEngine(){
    delete sceneMan;
}

void GD_ScenedGameEngine::init(){
    sceneMan = GD_SceneManager::createInstance();
    std::srand(std::time(nullptr));
}

void GD_ScenedGameEngine::update(sf::Time deltaTime){
    sceneMan->updateCurrentScene(deltaTime);
}

void GD_ScenedGameEngine::draw(sf::RenderWindow *window){
    sceneMan->drawCurrentScene(window);
}

void GD_ScenedGameEngine::keyPressTrigger(sf::Keyboard::Scan keyCode){

}

void GD_ScenedGameEngine::keyReleaseTrigger(sf::Keyboard::Scan keyCode){

}

GD_SceneManager* GD_ScenedGameEngine::getSceneManager(){
    return sceneMan;
}

