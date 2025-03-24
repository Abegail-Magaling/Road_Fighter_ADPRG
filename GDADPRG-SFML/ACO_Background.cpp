#include "ACO_Background.h"

void ACO_Background::scaleSprite(sf::Sprite *sprite, sf::IntRect rect, 
        float tWidth, float tHeight){
    sprite->setScale({tWidth/rect.size.x, tHeight/rect.size.y});
}

ACO_Background::ACO_Background(std::string id,std::string spriteType,
        float cellSize,int numRow,int numCol,int xOffset,int yOffset):
        GD_GameObject(id){
    GD_GameResource* res = GD_GameResource::createInstance();
    sf::IntRect textureBox = (*res->getAtlas())[spriteType];
    for(int i=0; i<numRow*numCol; i++){
        sprites.push_back(sf::Sprite(*res->getTexture(),textureBox));
        scaleSprite(&sprites.back(), textureBox, cellSize, cellSize);
    }
    
    for(int i=0; i<numRow*numCol; i++)
        sprites[i].setPosition({
            xOffset+(i%numCol)*cellSize,
            yOffset+(i/numCol)*cellSize});
}

void ACO_Background::init(){
    
}

void ACO_Background::update(sf::Time deltaTime){}

void ACO_Background::draw(sf::RenderWindow *window){
    for(int i=0; i<sprites.size(); i++)
        window->draw(sprites[i]);
}
