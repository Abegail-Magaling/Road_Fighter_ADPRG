#include "ACO_GameData.h"

ACO_GameData* ACO_GameData::myInstance = nullptr;

ACO_GameData* ACO_GameData::createInstance(){
    if(myInstance == nullptr)
        myInstance = new ACO_GameData();
    return myInstance;
}
ACO_GameData::ACO_GameData(){this->score = 0;}
void ACO_GameData::addScore(int val){this->score += val;}
int ACO_GameData::getScore(){ return score; }
void ACO_GameData::addObjSnapshot(GD_GameObject* obj){snapshot.push_back(obj);}
void ACO_GameData::clearObjSnapshot(){snapshot.clear();}
std::vector<GD_GameObject*> ACO_GameData::getObjSnapshot(){return snapshot;}
