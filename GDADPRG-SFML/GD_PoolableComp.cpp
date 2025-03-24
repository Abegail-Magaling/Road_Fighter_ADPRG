#include "GD_PoolableComp.h"

GD_PoolableComp::GD_PoolableComp():
        GD_Component("GD_PoolableObject"){
    active = false;
}

void GD_PoolableComp::perform(sf::Time deltaTime){}
bool GD_PoolableComp::isActive(){ return active; }
void GD_PoolableComp::setActive(bool val){ active=val; }
