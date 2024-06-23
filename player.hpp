#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "board.hpp"


using namespace std;

namespace ariel
{
    class board;
    class player
    {
    private:
        string name;
        int victoryPoints;
        int playerNum; //1-3
        int wood;
        int bricks;
        int wheat;
        int ore;
        int wool;

    public:
        player(string name, int playerNum);
        int placeSettlement(int vertexNum, board* b);
        int placeRoad(int v1, int v2, board* b);
        void addResource(string resource, int amount);
        void rollDice(board* b);
        int getPlayerNum();
        int getVictoryPoints(){
            return this->victoryPoints;
        }
        void firstSettlements(int v1, int v2 ,board* b);
        string getName(){
            return this->name;
        }
        void trade(player* p);
        void printResources();
    };
} // namespace ariel