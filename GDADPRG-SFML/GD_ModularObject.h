#pragma once

class GD_Component;

#include "GD_2DBlockObject.h"
#include "GD_Component.h"
#include <string>

class GD_ModularObject: public GD_2DBlockObject{
	private:
		std::vector<GD_Component*> componentList;
	public:
        GD_ModularObject(std::string objName, std::string textureName, float tileSize);
        ~GD_ModularObject();
        void attachComponent(GD_Component* component);
        GD_Component* getComponent(std::string componentName);
        void update(sf::Time deltaTime);
};
