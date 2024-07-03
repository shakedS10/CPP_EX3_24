#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "board.hpp"
#include "card.hpp"


using namespace std;

namespace ariel
{
    class board;
    class card;
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
        vector<card*> cards;
        int knightCount;

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
        void buyCard(board* b);
        void addCard(card* c);
        void showCards();
        void useCard(int i,board* b);
        int getwood(){
            return this->wood;
        }
        int getbricks(){
            return this->bricks;
        }
        int getwheat(){
            return this->wheat;
        }
        int getore(){
            return this->ore;
        }
        int getwool(){
            return this->wool;
        }
        void removeKnight();
        void removeVictoryCard();
    };
} // namespace ariel