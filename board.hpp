#pragma once
#include <iostream>
#include "hexagon.hpp"
#include <vector>
#include <string>
#include <random>
#include<iomanip>
#include "card.hpp"

using namespace std;

namespace ariel{

class vertex;
class side;
class hexagon;
class player;
class card;
class board{
    protected:
    vector<vector<hexagon*>> hexagonboard = vector<vector<hexagon*>>();
    vector<vertex*> vertices = vector<vertex*>(54, nullptr);
    vector<side*> sides = vector<side*>();
    int turn;
    vector<int> rndNumbers = vector<int>(19, 0);
    vector<player*> players = vector<player*>();
    vector<card*> cards = vector<card*>();
    int longestRecRoad = 4;

    public:
    board();
    void printBoard();
    void setOcupiedCity(int playernum, int v);
    void setOcupiedRoad(int playernum, int v1, int v2);
    board* getBoard();
    int rollDices();
    void addPlayer(player* p);
    bool checkPlayer(int num);
    void nextTurn();
    int getTurn(){
        return this->turn;
    }
    void firstSettlements(player* p,int v1, int v2);
    string getNameFromTurn();
    player* getPlayerFromTurn(){
        return this->players[this->turn-1];
    }
    int isGameEnd(); // 0 - game not ended, 1 - player 1 won, 2 - player 2 won, 3 - player 3 won
    player* getPlayerByName(string name);
    vertex* getVertex(int i){
        if(i>-1 && i<54){
            return this->vertices[i];
        }
        throw invalid_argument("vertex number is invalid");
    }
    void takeCard(player* p);
    void monopoly(player* p);
    vector<side*> getSides(){
        return this->sides;
    }

};
} // namespace ariel