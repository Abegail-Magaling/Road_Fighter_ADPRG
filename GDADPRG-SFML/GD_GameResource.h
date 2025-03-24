#pragma once

#include "GD_AtlasParserM.h"
#include <SFML/Graphics.hpp>

class GD_GameResource{
	public:
		static GD_GameResource* createInstance();
		std::unordered_map<std::string,sf::IntRect>* getAtlas();
		sf::Texture* getTexture();
		sf::Font* getFont();
	private:
		static GD_GameResource* myInstance;
		std::unordered_map<std::string,sf::IntRect>* atlas;
		sf::Texture texture;
		sf::Font font;
		GD_GameResource();
};
