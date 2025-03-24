#pragma once

class GD_ModularObject;

#include "GD_GameObject.h"
#include "GD_ModularObject.h"

class GD_Component{
     private:
        std::string name;
        GD_ModularObject* owner;
    public:
        GD_Component(std::string name);
        void attachOwner(GD_ModularObject* owner);
        GD_ModularObject* getOwner();
        std::string getName();
        virtual void perform(sf::Time deltaTime) = 0;
};
