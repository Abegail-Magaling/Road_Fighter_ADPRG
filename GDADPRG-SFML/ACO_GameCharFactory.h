#pragma once

#include "GD_ModularObject.h"
#include "ACO_ChargeComp.h"
#include "ACO_ColliderComp.h"
#include "ACO_CharHealthComp.h"
#include "ACO_EnemyAIComp.h"

class ACO_GameCharFactory{
	public:
	    static GD_ModularObject* makePlayer(float tileSize,int x,int y);
	    static GD_ModularObject* makeEnemy(int id,float tileSize,
	        GD_ModularObject* player,int x,int y);
	    static GD_ModularObject* makeSide(int id,float tileSize,
	        GD_ModularObject* player);
	    static GD_ModularObject* makeBonus(int id,float tileSize,int gridSize);
};
