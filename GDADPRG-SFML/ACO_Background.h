#pragma once

#include "GD_GameObject.h"
#include "GD_GameResource.h"

class ACO_Background: public GD_GameObject{
	private:
		std::vector<sf::Sprite> sprites;
		sf::Texture texture;
	public:
	    ACO_Background(std::string id,std::string spriteType,
	        float cellSize,int numRow,int numCol,int xOffset,int yOffset); 
        void scaleSprite(sf::Sprite *sprite, sf::IntRect rect, 
		    float tWidth, float tHeight);
		
        void init();
        void update(sf::Time deltaTime);
        void draw(sf::RenderWindow *window);
};
