#include "GD_Trn.h"

void GD_Trn::moveUp(GD_2DBlockObject* obj){
    int x = obj->getTileX() + 0;
    int y = obj->getTileY() - 1; 
    obj->setTileXY(x,y);
    for(GD_2DBlockObject* ch: obj->getAllChildren())
        moveUp(ch);
}

void GD_Trn::moveDown(GD_2DBlockObject* obj){
    int x = obj->getTileX() + 0;
    int y = obj->getTileY() + 1; 
    obj->setTileXY(x,y);
    for(GD_2DBlockObject* ch: obj->getAllChildren())
        moveDown(ch);
}

void GD_Trn::moveLeft(GD_2DBlockObject* obj){
    int x = obj->getTileX() - 1;
    int y = obj->getTileY() + 0; 
    obj->setTileXY(x,y);
    for(GD_2DBlockObject* ch: obj->getAllChildren())
        moveLeft(ch);
}

void GD_Trn::moveRight(GD_2DBlockObject* obj){
    int x = obj->getTileX() + 1;
    int y = obj->getTileY() + 0; 
    obj->setTileXY(x,y);
    for(GD_2DBlockObject* ch: obj->getAllChildren())
        moveRight(ch);
}

void GD_Trn::turnLeft(GD_2DBlockObject* obj){
    obj->getSprite()->rotate(sf::degrees(-90));
    for(GD_2DBlockObject* ch: obj->getAllChildren()){
        int x = obj->getTileX() + (obj->getTileY() - ch->getTileY());
        int y = obj->getTileY() + (obj->getTileX() - ch->getTileX());
        ch->setTileXY(x,y);
        turnLeft(ch);
    }//end for
}

void GD_Trn::turnRight(GD_2DBlockObject* obj){
    obj->getSprite()->rotate(sf::degrees(90));
    for(GD_2DBlockObject* ch: obj->getAllChildren()){
        int x = obj->getTileX() + (obj->getTileY() - ch->getTileY());
        int y = obj->getTileY() + (obj->getTileX() - ch->getTileX());
        ch->setTileXY(x,y);
        turnRight(ch);
    }//end for
}

void GD_Trn::moveToRand(GD_2DBlockObject* obj,int gridSize){
    int xPos = std::rand()%gridSize;
    int yPos = std::rand()%gridSize;
    obj->setTileXY(xPos,yPos);
}

