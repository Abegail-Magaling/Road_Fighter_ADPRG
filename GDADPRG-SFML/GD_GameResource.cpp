#include "GD_GameResource.h"

GD_GameResource* GD_GameResource::myInstance = nullptr;

GD_GameResource::GD_GameResource(){
    if(texture.loadFromFile("animalcity.png")
            && font.openFromFile("OpenSans-Medium.ttf") ){
        atlas = createDictionary("animalcity.atlas");
	}
}

GD_GameResource* GD_GameResource::createInstance(){
    if(myInstance == nullptr)
        myInstance = new GD_GameResource();
    return myInstance;
}

std::unordered_map<std::string,sf::IntRect>* GD_GameResource::getAtlas(){
    return atlas;
}
sf::Texture* GD_GameResource::getTexture(){
    return &texture;
}
sf::Font* GD_GameResource::getFont(){
    return &font;
}
