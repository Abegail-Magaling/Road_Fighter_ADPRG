#pragma once

#include "GD_Component.h"
#include "GD_ModularObject.h"
#include <SFML/Graphics.hpp>

class ACO_ChargeComp: public GD_Component{
	public:
	    ACO_ChargeComp();
	    void perform(sf::Time deltaTime);
	    void startCharge();
	    void endCharge();
	    bool isCharging();
	    int getChargeLevel();
	private:
	    sf::Time chargeTime;
	    bool chargeActive;
};
