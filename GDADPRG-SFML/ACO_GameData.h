#pragma once

#include "GD_Component.h"
#include "GD_GameObject.h"
#include <vector>

class ACO_GameData{
	public:
	    static ACO_GameData* createInstance();
	    
	    void addScore(int val);
        int getScore();
        void addObjSnapshot(GD_GameObject* obj);
        void clearObjSnapshot();
        std::vector<GD_GameObject*> getObjSnapshot();
    private:
        static ACO_GameData* myInstance;
        int score;
        std::vector<GD_GameObject*> snapshot;
        ACO_GameData();
        
};
