#pragma once

#include <iostream>
#include "vertex.hpp"
#include <vector>


using namespace std;
namespace ariel{
    class vertex;
    class side
    {
    protected:
    bool isOccupied;
    int id;
    int player;
    vector<vertex*> owners = vector<vertex*>();


    public:
    side(vertex* v1, vertex* v2, int id);
    void setOcupied(int num);
    vector<vertex*> getOwners();
    bool getIsOccupied(){
        return this->isOccupied;
    }
    int getId(){
        return this->id;
    }
    int getPlayer(){
        return this->player;
    }
    bool canBuildRoad(int num);

    
};
}
    
        