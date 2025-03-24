#include "ACO_ChargeComp.h"

ACO_ChargeComp::ACO_ChargeComp():
        GD_Component("ACO_ChargeComp"){
    chargeTime = sf::Time::Zero;
    chargeActive = false;
}

void ACO_ChargeComp::perform(sf::Time deltaTime){
    if(chargeActive){
        chargeTime += deltaTime;
        std::cout << chargeTime.asSeconds() << std::endl;
    }
}

void ACO_ChargeComp::startCharge(){
    chargeTime = sf::Time::Zero;
    chargeActive = true;
}

void ACO_ChargeComp::endCharge(){
    chargeActive = false;
}

bool ACO_ChargeComp::isCharging(){
    return chargeActive;
}

int ACO_ChargeComp::getChargeLevel(){
    return (int)chargeTime.asSeconds();
}
