#pragma once

#include "GD_Component.h"

class GD_PoolableComp: public GD_Component{
    private:
        bool active;
	public:
	    GD_PoolableComp();
	    void perform(sf::Time deltaTime);
	    bool isActive();
	    void setActive(bool val);
};
