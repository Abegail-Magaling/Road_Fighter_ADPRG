#include "ACO_EnemyAIComp.h"

ACO_EnemyAIComp::ACO_EnemyAIComp(GD_ModularObject* target):
        GD_Component("ACO_EnemyAIComp"){
    this->target = target;
    time = sf::Time::Zero;
}

void ACO_EnemyAIComp::perform(sf::Time deltaTime){
    time += deltaTime;
    if(time.asSeconds()<1) return;

    time = sf::Time::Zero;
    GD_ModularObject* enemy = getOwner();
    
    int xDif = target->getTileX() - enemy->getTileX();
    int yDif = target->getTileY() - enemy->getTileY();
    
    if(std::abs(xDif) > std::abs(yDif)){
        if(xDif>0) GD_Trn::moveRight(enemy);
        else GD_Trn::moveLeft(enemy);
    }else{
        if(yDif>0) GD_Trn::moveDown(enemy);
        else GD_Trn::moveUp(enemy);
    }
}
