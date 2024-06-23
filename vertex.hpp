#pragma once
#include <iostream>
#include "side.hpp"
#include <vector>


using namespace std;

namespace ariel{
class side;

class vertex
{
    protected:
    int isOccupied; // 0 = not occupied, 1 = occupied town, 2 = occupied city
    int player;
    int id;
    vector<vertex*> neighbors = vector<vertex*>();
    vector<side*> sides = vector<side*>();



    public:
    vertex(int id);
    void setOcupied(int num);
    vector<vertex*> getNeighbors();
    vector<side*> getSides();
    void addNeighbor(vertex* v, side* s);
    int getId(){
        return this->id;}
    int getIsOccupied(){
        return this->isOccupied;
    }
    int getPlayer(){
        return this->player;
    }
    bool canBuildTown(int num);
    
};
}

    
        