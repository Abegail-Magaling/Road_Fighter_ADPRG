#pragma once

#include "GD_GameObject.h"
#include "GD_GameResource.h"

class GD_2DBlockObject: public GD_GameObject{
	private:
		GD_2DBlockObject* parent;
		std::vector<GD_2DBlockObject*> children;
		sf::Sprite* sprite; 
		int x, y;
		float tileSideSize;
		bool visible;
	public:
	    GD_2DBlockObject(std::string objName, std::string textureName, float tileSize);
	    ~GD_2DBlockObject();
	    
	    void setParent(GD_2DBlockObject* parentVal);
        void attachChild(GD_2DBlockObject* child);
        GD_2DBlockObject* getParent();
        GD_2DBlockObject* getChild(std::string objName);
        std::vector<GD_2DBlockObject*> getAllChildren();
        
        bool isVisible();
        void toggleVisibility();
        sf::Sprite* getSprite();
        
        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();
        float getTileSize();
        
        void init();
        void update(sf::Time deltaTime);
        void draw(sf::RenderWindow *window);
};
