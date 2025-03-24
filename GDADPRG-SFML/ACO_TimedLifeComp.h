#pragma once

#include "GD_Component.h"

class ACO_TimedLifeComp: public GD_Component{
	public:
	    ACO_TimedLifeComp(float lifeTimeInSec);
	    void resetLife(float lifeTimeInSec);
	    void perform(sf::Time deltaTime);
	    bool isElapsed();
    private:
        float lifeTimeInSec;
};
