#include "ACO_BulletMovementComp.h"

ACO_BulletMovementComp::ACO_BulletMovementComp():
        GD_Component("ACO_BulletMovementComp"){
    moveDirection = UP;
    moveSpeed = 1.f;
    elapsedTime = sf::Time::Zero;
}

void ACO_BulletMovementComp::perform(sf::Time deltaTime){
    elapsedTime += deltaTime;
    if(elapsedTime.asSeconds()<moveSpeed) return;
    elapsedTime = sf::Time::Zero;
    
    GD_ModularObject* owner = getOwner();
    switch(moveDirection){
        case UP: GD_Trn::moveUp(owner); break;
        case DOWN: GD_Trn::moveDown(owner); break;
        case LEFT: GD_Trn::moveLeft(owner); break;
        case RIGHT: GD_Trn::moveRight(owner); break;
    }
    
}

void ACO_BulletMovementComp::setDirection(Direction direction){
    moveDirection = direction;
}

void ACO_BulletMovementComp::setSpeed(float speed){
    moveSpeed = speed;
}
