#pragma once

#include "GD_Component.h"
#include "GD_ModularObject.h"
#include "GD_Trn.h"

class ACO_EnemyAIComp: public GD_Component{
	public:
	    ACO_EnemyAIComp(GD_ModularObject* target);
	    void perform(sf::Time deltaTime);
    private:
        GD_ModularObject* target;
        sf::Time time;
};
