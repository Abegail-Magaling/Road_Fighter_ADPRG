#include "ACO_TimedLifeComp.h"

ACO_TimedLifeComp::ACO_TimedLifeComp(float lifeTimeInSec):
        GD_Component("ACO_TimedLifeComp"){
    this->lifeTimeInSec = lifeTimeInSec;
}

void ACO_TimedLifeComp::resetLife(float lifeTimeInSec){
    this->lifeTimeInSec = lifeTimeInSec;
}

void ACO_TimedLifeComp::perform(sf::Time deltaTime){
    if(lifeTimeInSec>=0)
        lifeTimeInSec -= deltaTime.asSeconds();
}

bool ACO_TimedLifeComp::isElapsed(){
    return lifeTimeInSec<=0;
}
