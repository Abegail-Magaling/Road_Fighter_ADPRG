#define TIME_LIFE 5.f
#include "ACO_BulletObject.h"

ACO_BulletObject::ACO_BulletObject(std::string objName, 
        std::string textureName,float tileSize):
        GD_ModularObject(objName,textureName,tileSize){
    this->size = 2;
    this->attachComponent(new ACO_BulletMovementComp());
    this->attachComponent(new ACO_ColliderComp(tileSize));
    this->attachComponent(new GD_PoolableComp());
    this->attachComponent(new ACO_TimedLifeComp(TIME_LIFE));
}

ACO_BulletObject::ACO_BulletObject(std::string objName, std::string textureName, 
            float tileSize,GD_ModularObject* spawner,int size):
            GD_ModularObject(objName,textureName,tileSize){
    this->size = 2;
    this->attachComponent(new ACO_BulletMovementComp());
    this->attachComponent(new ACO_ColliderComp(tileSize));
    this->attachComponent(new GD_PoolableComp());
    this->attachComponent(new ACO_TimedLifeComp(TIME_LIFE));
    
    resizeBullet(size);
    positionBullet(spawner);
}

void ACO_BulletObject::resizeBullet(int size){
    sf::Vector2f sc = this->getSprite()->getScale();
    if(size==1 && this->size==2){
        sc.x = sc.x/2;
        sc.y = sc.y/2;
    }else if(size==2 && this->size==1){
        sc.x = sc.x*2;
        sc.y = sc.y*2;
    }
    if(this->size != size){
        this->getSprite()->setScale(sc);
        this->size = size;
    }
}

void ACO_BulletObject::positionBullet(GD_ModularObject* spawner){
    this->setTileXY(spawner->getTileX(),spawner->getTileY());
    
    int direction = spawner->getSprite()->getRotation().asDegrees()/89;
    ACO_BulletMovementComp* mc = (ACO_BulletMovementComp*)getComponent("ACO_BulletMovementComp");
    switch(direction%4){
        case 0: GD_Trn::moveUp(this);
            mc->setDirection(ACO_BulletMovementComp::Direction::UP);
            break;
        case 1: GD_Trn::moveRight(this);
            mc->setDirection(ACO_BulletMovementComp::Direction::RIGHT);
            break;
        case 2: GD_Trn::moveDown(this);
            mc->setDirection(ACO_BulletMovementComp::Direction::DOWN);
            break;
        case 3: GD_Trn::moveLeft(this);
            mc->setDirection(ACO_BulletMovementComp::Direction::LEFT);
            break;
    }//end switch
                
    this->getSprite()->setRotation(
        spawner->getSprite()->getRotation()
    );
}

void ACO_BulletObject::resetLife(){
    ACO_TimedLifeComp* tl = (ACO_TimedLifeComp*)getComponent("ACO_TimedLifeComp");
    tl->resetLife(TIME_LIFE);
}

bool ACO_BulletObject::isExpired(){
    ACO_TimedLifeComp* tl = (ACO_TimedLifeComp*)getComponent("ACO_TimedLifeComp");
    if(tl!=nullptr)
        return tl->isElapsed();
    return false;
}

int ACO_BulletObject::getBulletSize(){
    return this->size;
}

