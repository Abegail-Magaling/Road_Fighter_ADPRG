#pragma once

#include "GD_Component.h"
#include "GD_ModularObject.h"
#include "GD_Trn.h"

class ACO_BulletMovementComp: public GD_Component{
	public:
	    enum Direction{ UP, DOWN, LEFT, RIGHT };
	    ACO_BulletMovementComp();
	    void perform(sf::Time deltaTime);
	    void setDirection(Direction direction);
	    void setSpeed(float speed);
	private:
	    Direction moveDirection;
        float moveSpeed;
        sf::Time elapsedTime;
};
