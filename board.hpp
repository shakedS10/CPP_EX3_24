#include <iostream>
#include "hexagon.hpp"
#include <vector>
#include <string>
#include <random>
#include<iomanip>
#pragma once

using namespace std;

namespace ariel{

class vertex;
class side;
class hexagon;
class board{
    protected:
    vector<vector<hexagon*>> hexagonboard = vector<vector<hexagon*>>();
    vector<vertex*> vertices = vector<vertex*>(54, nullptr);
    vector<side*> sides = vector<side*>();
    int turn;
    vector<int> rndNumbers = vector<int>(19, 0);

    public:
    board();
    void printBoard();
    void setOcupiedCity(int playernum, int v);
    void setOcupiedRoad(int playernum, int v1, int v2);
    board* getBoard();

};
} // namespace ariel