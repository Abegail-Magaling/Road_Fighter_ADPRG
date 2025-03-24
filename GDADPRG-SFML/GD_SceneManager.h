#pragma once

#include "GD_Scene.h"
#include <SFML/Graphics.hpp>
#include <vector>

class GD_SceneManager{
    public:
	    static GD_SceneManager* createInstance();
	    void registerScene(GD_Scene* scene);
	    GD_Scene* loadScene(std::string id);
	    GD_Scene* getCurrentScene();
	    void updateCurrentScene(sf::Time deltaTime);
	    void drawCurrentScene(sf::RenderWindow *window);
	    ~GD_SceneManager();
    private:
        static GD_SceneManager* myInstance;
        std::vector<GD_Scene*> scenes;
        GD_Scene* currentScene;
        GD_SceneManager();
        GD_Scene* findScene(std::string name);
};
