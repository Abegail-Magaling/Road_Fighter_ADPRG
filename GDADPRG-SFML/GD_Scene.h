#pragma once

#include "GD_GameObject.h"
#include "GD_ModularObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class GD_Scene{
    private:
        std::string name;
        std::vector<GD_GameObject*> objects;
    public:
        GD_Scene(std::string name);
        ~GD_Scene();
        std::string getName();
        
        virtual void onLoad() = 0;
        virtual void update(sf::Time deltaTime);
        virtual void draw(sf::RenderWindow* window);
        virtual void onUnload() = 0;
        
        void addObject(GD_GameObject* obj);
        GD_GameObject* findObject(std::string id);
        std::vector<GD_GameObject*> getAllObjects();
        void removeObject(std::string id);
        void removeObject(GD_GameObject *obj);
        void removeAllObjects();
};
