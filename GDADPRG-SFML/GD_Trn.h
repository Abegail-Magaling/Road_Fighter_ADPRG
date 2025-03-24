#pragma once

#include "GD_2DBlockObject.h"

class GD_Trn{
	public:
	    static void moveUp(GD_2DBlockObject* obj);
	    static void moveDown(GD_2DBlockObject* obj);
	    static void moveLeft(GD_2DBlockObject* obj);
	    static void moveRight(GD_2DBlockObject* obj);
	    static void turnLeft(GD_2DBlockObject* obj);
	    static void turnRight(GD_2DBlockObject* obj);
	    static void moveToRand(GD_2DBlockObject* obj,int gridSize);
};
