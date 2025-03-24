#include "ACO_CharHealthComp.h"

ACO_CharHealthComp::ACO_CharHealthComp(int hp):
        GD_Component("ACO_CharHealthComp"){
    this->hp = hp;
}

void ACO_CharHealthComp::setHP(int hp){
    this->hp = hp;
}

void ACO_CharHealthComp::decreaseHP(int value){
    hp -= value;
}

int ACO_CharHealthComp::getHP(){
    return hp;
}

void ACO_CharHealthComp::perform(sf::Time deltaTime){}
