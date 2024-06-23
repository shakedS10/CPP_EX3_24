#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "player.hpp"




using namespace std;

namespace ariel{
    player::player(string name,int num){
        this->name = name;
        this->playerNum = num;
        this->victoryPoints = 2;
        this->wood = 0;
        this->bricks = 0;
        this->wheat = 0;
        this->ore = 0;
        this->wool = 0;
    }

    int player::placeSettlement(int vertexNum, board* b){
        if(b->checkPlayer(this->playerNum)){
            b->setOcupiedCity(this->playerNum, vertexNum);
            this->victoryPoints++;    
        }
        return 0;
    }

    int player::placeRoad(int v1, int v2, board* b){
        if(b->checkPlayer(this->playerNum)){
            b->setOcupiedRoad(this->playerNum,v1, v2);
        }
        return 0;
    }

    void player::addResource(string resource, int amount){
        if(resource == "Forest"|| resource == "wood"){
            this->wood += amount;
        }
        else if(resource == "Hills"|| resource == "bricks"){
            this->bricks += amount;
        }
        else if(resource == "Fields"|| resource == "wheat"){
            this->wheat += amount;
        }
        else if(resource == "Mountains"|| resource == "ore"){
            this->ore += amount;
        } 
        else if(resource == "Pasture"|| resource == "wool"){
            this->wool += amount;
        }
    }

    int player::getPlayerNum(){
        return this->playerNum;
    }

    void player::firstSettlements(int v1,int v2 ,  board* b){
        if(b->checkPlayer(this->playerNum)){
            b->firstSettlements(this, v1, v2);
            this->victoryPoints++;
        }
    }

    void player::rollDice(board* b){
        if(b->checkPlayer(this->playerNum)){
            int num = b->rollDices();
            cout << "You rolled " << num << endl;
        }
    }

    void player::trade(player* p){
        this->printResources();
        bool flag = true;
        map<string, int> give;
        while(flag){
            cout << "Choose resource to give" << endl;
            int resource;
            cout << "1 - wood" << endl;
            cout << "2 - bricks" << endl;
            cout << "3 - wheat" << endl;
            cout << "4 - ore" << endl;
            cout << "5 - wool" << endl;
            cout << "6 - choose receive" << endl;
            std::cin >> resource;
            if(resource == 6){
                flag = false;
                break;
            }
            cout << "Choose amount" << endl;
            int amount;
            cin >> amount;
            switch (resource)
            {
                case 1:
                    if(this->wood >= amount){
                        give["wood"] = amount;
                    }
                    else{
                        cout << "Not enough wood" << endl;
                    }
                    break;
                case 2:
                    if(this->bricks >= amount){
                        give["bricks"] = amount;
                    }
                    else{
                        cout << "Not enough bricks" << endl;
                    }
                    break;
                case 3:
                    if(this->wheat >= amount){
                        give["wheat"] = amount;
                    }
                    else{
                        cout << "Not enough wheat" << endl;
                    }
                    break;
                case 4:

                    if(this->ore >= amount){
                        give["ore"] = amount;
                    }
                    else{
                        cout << "Not enough ore" << endl;
                    }
                    break;
                case 5:

                    if(this->wool >= amount){
                        give["wool"] = amount;
                    }
                    else{
                        cout << "Not enough wool" << endl;
                    }
                    break;
                
            }
        }
        p->printResources();
        map<string, int> receive;
        flag = true;
        while(flag){
            cout << "Choose resource to receive" << endl;
            int resource;
            cout << "1 - wood" << endl;
            cout << "2 - bricks" << endl;
            cout << "3 - wheat" << endl;
            cout << "4 - ore" << endl;
            cout << "5 - wool" << endl;
            cout << "6 - finish offer" << endl;
            cin >> resource;
            if(resource == 6){
                flag = false;
                break;
            }
            cout << "Choose amount" << endl;
            int amount;
            cin >> amount;
            switch (resource)
            {
                case 1:
                    if(p->wood >= amount){
                    receive["wood"] = amount;
                    }
                    break;
                case 2:
                    if(p->bricks >= amount){
                    receive["bricks"] = amount;
                    }
                    break;
                case 3:
                    if(p->wheat >= amount){
                    receive["wheat"] = amount;
                    }
                    break;
                case 4:

                    if(p->ore >= amount){
                    receive["ore"] = amount;
                    }
                    break;
                case 5: 
                    if(p->wool >= amount){
                    receive["wool"] = amount;
                    }
                    break;
            }
        }
        cout << p->getName() << " do you accept the offer?" << endl;
        cout << "y/n" << endl;
        char ans;
        cin >> ans;
        if(ans == 'y'){
            for(auto it = give.begin(); it != give.end(); it++){
                this->addResource(it->first, -it->second);
                p->addResource(it->first, it->second);
            }
            for(auto it = receive.begin(); it != receive.end(); it++){
                this->addResource(it->first, it->second);
                p->addResource(it->first, -it->second);
            }
        }
        if(ans == 'n'){
            cout << "Trade declined" << endl;
        }

    }

    void player::printResources(){
        cout << this->name << " resources:" << endl;
        cout << "Wood: " << this->wood << endl;
        cout << "Bricks: " << this->bricks << endl;
        cout << "Wheat: " << this->wheat << endl;
        cout << "Ore: " << this->ore << endl;
        cout << "Wool: " << this->wool << endl;
    }
} // namespace ariel

