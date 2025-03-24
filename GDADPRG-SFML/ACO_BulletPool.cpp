#include "ACO_BulletPool.h"

ACO_BulletPool::ACO_BulletPool(int maxPoolSize,int tileSize){
    this->maxPoolSize = maxPoolSize;
    this->tileSize = tileSize;
}

ACO_BulletPool::~ACO_BulletPool(){
    for(ACO_BulletObject* bl: objectPool)
        if(bl!=nullptr)
            delete bl;
}

ACO_BulletObject* ACO_BulletPool::requestObject(){
    for(int i=0; i<objectPool.size(); i++){
        ACO_BulletObject* bl = objectPool[i];
        if(bl!=nullptr){
            std::cout << " Aquire: " << bl->getName() << std::endl;
            objectPool[i] = nullptr;
            return bl;
        }
    }
    if(objectPool.size()<maxPoolSize){
        objectPool.push_back(nullptr);
        ACO_BulletObject* bl = new ACO_BulletObject(
            "bullet"+std::to_string(objectPool.size()),
            "shot1",tileSize);
        std::cout << " Aquire: " << bl->getName() << std::endl;
        return bl;
    }
    std::cout << " Cannot create bullet"<< std::endl;
    return nullptr;
}
        
void ACO_BulletPool::releaseObject(ACO_BulletObject* bullet){
    for(int i=0; i<objectPool.size(); i++)
        if(objectPool[i]==nullptr){
            std::cout << "Release: " << bullet->getName() << std::endl;
            objectPool[i] = bullet;
            bullet->setTileXY(-1,-1);
            return;
        }
}
