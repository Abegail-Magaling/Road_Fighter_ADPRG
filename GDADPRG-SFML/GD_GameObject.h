#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class GD_GameObject{
	private:
		std::string name;
	public:
	    GD_GameObject(std::string objName);
	    std::string getName();
		virtual void init() = 0;
        virtual void update(sf::Time deltaTime) = 0;
        virtual void draw(sf::RenderWindow *window) = 0;
};
