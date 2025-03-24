#pragma once

#include "GD_ModularObject.h"
#include "ACO_BulletMovementComp.h"
#include "ACO_ColliderComp.h"
#include "GD_PoolableComp.h"
#include "ACO_TimedLifeComp.h"
#include "GD_Trn.h"
#include <SFML/Graphics.hpp>

class ACO_BulletObject: public GD_ModularObject{
	private:
		int size;
	public:
	    ACO_BulletObject(std::string objName, std::string textureName,float tileSize);
	    ACO_BulletObject(std::string objName, std::string textureName, 
            float tileSize,GD_ModularObject* spawner,int size);
        void resizeBullet(int size);
        void positionBullet(GD_ModularObject* spawner);
        void resetLife();
        bool isExpired();
        int getBulletSize();
};
