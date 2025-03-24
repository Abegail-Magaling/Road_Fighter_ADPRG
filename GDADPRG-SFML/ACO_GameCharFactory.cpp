#include "ACO_GameCharFactory.h"

GD_ModularObject* ACO_GameCharFactory::makePlayer(float tileSize,int x,int y){
    GD_ModularObject* player = new GD_ModularObject("player","crab",tileSize);
    player->attachComponent(new ACO_ChargeComp());
    player->attachComponent(new ACO_ColliderComp(tileSize));
    player->attachComponent(new ACO_CharHealthComp(6));
    player->setTileXY(x,y);
    return player;
}

GD_ModularObject* ACO_GameCharFactory::makeEnemy(int id,float tileSize,
        GD_ModularObject* player,int x,int y){
    GD_ModularObject* enemy = new GD_ModularObject(
        "enemy"+std::to_string(id),
        "enemy"+std::to_string(id%3+1),tileSize);
    enemy->attachComponent(new ACO_EnemyAIComp(player));
    enemy->attachComponent(new ACO_ColliderComp(tileSize));
    enemy->attachComponent(new ACO_CharHealthComp(4));
    //enemy->toggleVisibility();
    enemy->setTileXY(x,y);
    return enemy;
}

GD_ModularObject* ACO_GameCharFactory::makeSide(int id,float tileSize,GD_ModularObject* player){
    std::string name = "side"+std::to_string(id);
    GD_ModularObject* side = new GD_ModularObject(name,"shot2",tileSize);
    side->attachComponent(new ACO_ColliderComp(tileSize));
    side->setTileXY(player->getTileX(),player->getTileY());
    if(id==1)
        GD_Trn::moveLeft(side);
    else if(id==2)
        GD_Trn::moveRight(side);
    player->attachChild(side);
    return side;
    
}
GD_ModularObject* ACO_GameCharFactory::makeBonus(int id,float tileSize,int gridSize){
    std::string name = "bonus"+std::to_string(id);
    GD_ModularObject* bonus = new GD_ModularObject(name,name,tileSize);
    bonus->attachComponent(new ACO_ColliderComp(tileSize));
    GD_Trn::moveToRand(bonus,gridSize);
    return bonus;
}
