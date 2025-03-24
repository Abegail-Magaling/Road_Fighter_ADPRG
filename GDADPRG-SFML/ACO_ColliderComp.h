#pragma once

#include "GD_Component.h"
#include "GD_ModularObject.h"
#include <SFML/Graphics.hpp>

class ACO_ColliderComp: public GD_Component{
	public:
	    ACO_ColliderComp(float tileSize);
	    void perform(sf::Time deltaTime);
	    float getX();
	    float getY();
	    float getWidth();
	    float getHeight();
    private:
        float tileSize;
};
