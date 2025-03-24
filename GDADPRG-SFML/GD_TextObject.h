#pragma once

#include "GD_GameObject.h"
#include "GD_GameResource.h"
#include <SFML/Graphics.hpp>
#include <string>

class GD_TextObject: public GD_GameObject{
	private:
		sf::Text* textObject;
	public:
        GD_TextObject(std::string id,std::string text,float x,float y);
        ~GD_TextObject();
        void setText(std::string text);
        void move(float x,float y);
        void init();
        void update(sf::Time deltaTime);
        void draw(sf::RenderWindow *window);
};
