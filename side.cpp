#include "side.hpp"
using namespace std;

namespace ariel{
    side::side(vertex* v1, vertex* v2, int id){
        this->isOccupied = false;
        this->owners.push_back(v1);
        this->owners.push_back(v2);
        this->id = id;
        this->player = 0;
    }

    void side::setOcupied(int num){
        this->isOccupied = true;
        this->player = num;
    }

    vector<vertex*> side::getOwners(){
        return this->owners;
    }
    
    bool side::canBuildRoad(int num){
        bool check = false;
        if(this->isOccupied == false){
            for(auto v : this->owners){
                if(v->getPlayer() == num){
                    check = true;
                }
            }
            cout << "check: " << check << endl;
            if(check == false){
                for(auto v : this->owners){
                    for(auto s : v->getSides()){
                        cout << "s->getPlayer(): " << s->getPlayer() << endl;
                        if(s->getPlayer() == num){
                            check = true;
                        }
                    }
                }
            }
        }
        cout << "check: " << check << endl;
        return check;

    }
} // namespace ariel