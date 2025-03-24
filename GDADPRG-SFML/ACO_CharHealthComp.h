#pragma once

#include "GD_Component.h"

class ACO_CharHealthComp: public GD_Component{
	public:
	    ACO_CharHealthComp(int hp);
	    void setHP(int hp);
	    void decreaseHP(int value);
	    int getHP();
	    void perform(sf::Time deltaTime);
    private:
        int hp;
};
