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
        this->knightCount = 0;
    }

    int player::placeSettlement(int vertexNum, board* b){
        if(b->getVertex(vertexNum)->getIsOccupied() == 0){
        if(this->wood < 1 || this->bricks < 1 || this->wheat < 1 || this->wool < 1){
            cout << "Not enough resources" << endl;
            return 1;
        }
        if(b->checkPlayer(this->playerNum)){
            b->setOcupiedCity(this->playerNum, vertexNum);
            this->victoryPoints++;
            this->wood--;
            this->bricks--;
            this->wheat--;
            this->wool--;
            return 0;
        }
        return 1;
        }
        else if (b->getVertex(vertexNum)->getIsOccupied() == 1){
            cout << "looking for upgrade" << endl;
            if(this->wheat < 2 || this->ore < 3){
                cout << "Not enough resources" << endl;
                return 1;
            }
            if(b->checkPlayer(this->playerNum)){
                b->setOcupiedCity(this->playerNum, vertexNum);
                this->victoryPoints++;
                this->wheat -= 2;
                this->ore -= 3;
                return 0;
            }
        }
        return 1;
    }

    int player::placeRoad(int v1, int v2, board* b){
        if(v1<0 || v1>53 || v2<0 || v2>53){
            cout << "Invalid vertex number" << endl;
            throw invalid_argument("Invalid vertex number");
        }
        if(this->wood < 1 || this->bricks < 1){
            cout << "Not enough resources" << endl;
            return 1;
        }
        if(b->checkPlayer(this->playerNum)){
            b->setOcupiedRoad(this->playerNum,v1, v2);
            this->wood--;
            this->bricks--;
            return 0;
        }
        return 1;
        
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
            cout << "Choose resource/card to give" << endl;
            int resource;
            cout << "1 - wood" << endl;
            cout << "2 - bricks" << endl;
            cout << "3 - wheat" << endl;
            cout << "4 - ore" << endl;
            cout << "5 - wool" << endl;
            cout << "6 - knight" << endl;
            cout << "7 - victory point" << endl;
            cout << "8 - year of plenty" << endl;
            cout << "9 - choose receive" << endl;
            
            std::cin >> resource;
            if(resource == 9){
                flag = false;
                break;
            }
            cout << "Choose amount" << endl;
            int amount;
            cin >> amount;
            switch (resource)
            {
                case 1:
                {
                    if(this->wood >= amount){
                        give["wood"] = amount;
                    }
                    else{
                        cout << "Not enough wood" << endl;
                    }
                }
                    break;
                case 2:
                {
                    if(this->bricks >= amount){
                        give["bricks"] = amount;
                    }
                    else{
                        cout << "Not enough bricks" << endl;
                    }
                }
                    break;
                case 3:
                {
                    if(this->wheat >= amount){
                        give["wheat"] = amount;
                    }
                    else{
                        cout << "Not enough wheat" << endl;
                    }
                }
                    break;
                case 4:
                {
                    if(this->ore >= amount){
                        give["ore"] = amount;
                    }
                    else{
                        cout << "Not enough ore" << endl;
                    }
                }
                    break;
                case 5:
                {
                    if(this->wool >= amount){
                        give["wool"] = amount;
                    }
                    else{
                        cout << "Not enough wool" << endl;
                    }
                }
                    break;
                case 6:
                 {
                    int count = 0;
                    for(auto c : this->cards){
                        if(c->getType() == 0){
                            count++;
                        }
                    }
                    if(count >= amount){
                        give["knight"] = amount;
                    }
                    else{
                        cout << "Not enough knights" << endl;
                    }
                 }
                    break;
                case 7:
                  {
                    int count = 0;
                    for(auto c : this->cards){
                        if(c->getType() == 1){
                            count++;
                        }
                    }
                    if(count >= amount){
                        give["victory point"] = amount;
                    }
                    else{
                        cout << "Not enough victory points" << endl;
                    }
                  }
                    break;
                case 8:
                {
                    int count = 0;
                    for(auto c : this->cards){
                        if(c->getType() == 2){
                            count++;
                        }
                    }
                    if(count >= amount){
                        give["year of plenty"] = amount;
                    }
                    else{
                        cout << "Not enough year of plentys" << endl;
                    }
                }
                    break;
                
            }
        }
        p->printResources();
        map<string, int> receive;
        flag = true;
        while(flag){
            cout << "Choose resource/card to receive" << endl;
            int resource;
            cout << "1 - wood" << endl;
            cout << "2 - bricks" << endl;
            cout << "3 - wheat" << endl;
            cout << "4 - ore" << endl;
            cout << "5 - wool" << endl;
            cout << "6 - knight" << endl;
            cout << "7 - victory point" << endl;
            cout << "8 - year of plenty" << endl;
            cout << "9 - finish offer" << endl;
            cin >> resource;
            if(resource == 9){
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
                case 6:
                    if(p->knightCount >= amount){
                    receive["knight"] = amount;
                    }
                    break;
                case 7:
                {
                    int count = 0;
                    for(auto c : p->cards){
                        if(c->getType() == 1){
                            count++;
                        }
                    }
                    if(count >= amount){
                    receive["victory point"] = amount;
                    }
                }
                    break;
                case 8:
                {
                    int count = 0;
                    for(auto c : p->cards){
                        if(c->getType() == 2){
                            count++;
                        }
                    }
                    if(count >= amount){
                    receive["year of plenty"] = amount;
                    }
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
                if(it->first == "knight"){
                    for(int i = 0; i < it->second; i++){
                        this->removeKnight();
                        p->addCard(new knight());
                    }
                }
                else if(it->first == "victory point"){
                    for(int i = 0; i < it->second; i++){
                        this->removeVictoryCard();
                        p->addCard(new victoryPoint());
                        
                    }
                }
                else if(it->first == "year of plenty"){
                    for(int i = 0; i < it->second; i++){
                        p->addCard(new yearOfPlenty());
                        for(auto c : this->cards){
                            if(c->getType() == 2){
                                this->cards.erase(this->cards.begin());
                                break;
                            }
                        }
                    }
                }
                else{
                    this->addResource(it->first, -it->second);
                    p->addResource(it->first, it->second);
                }
            }
            for(auto it = receive.begin(); it != receive.end(); it++){
                if(it->first == "knight"){
                    for(int i = 0; i < it->second; i++){
                        this->addCard(new knight());
                        p->removeKnight();
                    }
                }
                else if(it->first == "victory point"){
                    for(int i = 0; i < it->second; i++){
                        this->addCard(new victoryPoint());
                        p->removeVictoryCard();
                    }
                }
                else if(it->first == "year of plenty"){
                    for(int i = 0; i < it->second; i++){
                        this->addCard(new yearOfPlenty());
                        for(auto c : p->cards){
                            if(c->getType() == 2){
                                p->cards.erase(p->cards.begin());
                                break;
                            }
                        }
                    }
                }
                else{
                    p->addResource(it->first, -it->second);
                    this->addResource(it->first, it->second);
                }
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

    void player::buyCard(board* b){
        if(this->ore < 1 || this->wool < 1 || this->wheat < 1){
            cout << "Not enough resources" << endl;
            return;
        }
        if(b->checkPlayer(this->playerNum)){
            b->takeCard(this);
            this->ore--;
            this->wool--;
            this->wheat--;
        }
    }

    void player::addCard(card* c){
        this->cards.push_back(c);
        if(c->getType() == 0){
            this->knightCount++;
            this->victoryPoints++;
            if(this->knightCount >= 3){
                this->victoryPoints += 2;
            }
        }
        if(c->getType() == 1){
            this->victoryPoints++;
        }
    }

    void player::showCards(){
        for(int i = 0; i < this->cards.size(); i++){
            cout << i << " - ";
            switch (this->cards[i]->getType())
            {
                case 0:
                    cout << "Knight" << endl;
                    break;
                case 1:
                    cout << "Victory Point" << endl;
                    break;
                case 2:
                    cout << "Year of Plenty" << endl;
                    break;
                case 3:
                    cout << "Biggest Army" << endl;
                    break;
                case 4:
                    cout << "Longest Road" << endl;
                    break;
                case 5:
                    cout << "Monopoly" << endl;
                    break;
                case 6:
                    cout << "Road Building" << endl;
                    break;
            }
        }
    }

    void player::useCard(int i,board* b){
        if(i >= this->cards.size()){
            cout << "Invalid card number" << endl;
            return;
        }
        switch (this->cards[i]->getType())
        {
            case 0:
                cout << "Showed Knight" << endl;
                break;
            case 1:
                cout << "Showed Victory Point" << endl;
                break;
            case 2:
                cout << "Year of Plenty" << endl;
                for(int i = 0 ; i<2;i++){
                    cout << "Choose resource to take" << endl;
                    cout << "1 - wood" << endl;
                    cout << "2 - bricks" << endl;
                    cout << "3 - wheat" << endl;
                    cout << "4 - ore" << endl;
                    cout << "5 - wool" << endl;
                    int resource;
                    cin >> resource;
                    switch (resource)
                    {
                        case 1:
                            this->addResource("wood", 1);
                            break;
                        case 2:
                            this->addResource("bricks", 1);
                            break;
                        case 3:
                            this->addResource("wheat", 1);
                            break;
                        case 4:
                            this->addResource("ore", 1);
                            break;
                        case 5:
                            this->addResource("wool", 1);
                            break;
                    }
                }
                break;
            case 3:
                cout << "Showed Biggest Army" << endl;
                break;
            case 4:
                cout << "Showed Longest Road" << endl;
                break;
            case 5:
                cout << "Monopoly" << endl;
                b->monopoly(this);
                break;
            case 6:
                cout << "Road Building" << endl;
                this->wood += 2;
                this->bricks += 2;
                for(int i = 0 ; i<2;i++){
                    cout << "Choose road to place" << endl;
                    int v1, v2;
                    cin >> v1 >> v2;
                    this->placeRoad(v1, v2, b);
                }
                break;
        }
        

    }

    void player::removeKnight(){
        this->knightCount--;
        if(this->knightCount < 3){
            this->victoryPoints -= 2;
        }
        for(int i = 0 ; i < this->cards.size(); i++){
            if(this->cards[i]->getType() == 0){
                this->cards.erase(this->cards.begin() + i);
                break;
            }
        }
    }

    void player::removeVictoryCard(){
        for(int i = 0 ; i < this->cards.size(); i++){
            if(this->cards[i]->getType() == 1){
                this->cards.erase(this->cards.begin() + i);
                break;
            }
        }
        this->victoryPoints--;
    }

} // namespace ariel

