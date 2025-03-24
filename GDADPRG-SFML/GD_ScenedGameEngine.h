#pragma once

#include "GD_BaseEngine.h"
#include "GD_SceneManager.h"
#include <cstdlib>
#include <ctime>

class GD_ScenedGameEngine: public GD_BaseEngine{
    public:
	    ~GD_ScenedGameEngine();
	    virtual void init();
        virtual void update(sf::Time deltaTime);
        virtual void draw(sf::RenderWindow *window);
        virtual void keyPressTrigger(sf::Keyboard::Scan keyCode);
        virtual void keyReleaseTrigger(sf::Keyboard::Scan keyCode);
        GD_SceneManager* getSceneManager();
    private:
        GD_SceneManager* sceneMan;
};
