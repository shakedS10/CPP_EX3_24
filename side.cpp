#include "side.hpp"
using namespace std;

namespace ariel{
    side::side(vertex* v1, vertex* v2, int id){
        this->isOccupied = false;
        this->owners.push_back(v1);
        this->owners.push_back(v2);
        this->id = id;
    }

    void side::setOcupied(int num){
        this->isOccupied = true;
        this->player = num;
    }

    vector<vertex*> side::getOwners(){
        return this->owners;
    }
} // namespace ariel