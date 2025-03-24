#pragma once

#include "GD_GameObject.h"
#include "GD_GameResource.h"

class ACO_Button: public GD_GameObject{
	public:
		ACO_Button(std::string name,std::string textVal);
		~ACO_Button();
		void init();
        void update(sf::Time deltaTime);
        void draw(sf::RenderWindow *window);
		
		void setPosition(float x,float y);
		void setSize(float width,float height);
		void setText(std::string value);
		
		void setBlinkTime(float blinkTime);
		void toggleSelected();
		bool isSelected();
	private:
		sf::RectangleShape* rec;
		sf::Text* text;
		sf::Font font;
		bool selected;
		float blinkTime;
		sf::Time elapsedTime;
};
