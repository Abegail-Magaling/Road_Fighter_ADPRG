#pragma once

#include "ACO_BulletObject.h"

class ACO_BulletPool{
	public:
	    ACO_BulletPool(int maxPoolSize,int tileSize);
	    ~ACO_BulletPool();
	    ACO_BulletObject* requestObject();
	    void releaseObject(ACO_BulletObject* bullet);
    private:
        std::vector<ACO_BulletObject*> objectPool;
        int maxPoolSize, tileSize;
};
