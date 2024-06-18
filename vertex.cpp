#include "vertex.hpp"
using namespace std;

namespace ariel{
    vertex::vertex(int id){
        this->isOccupied = 0;
        this->id = id;
    }

    void vertex::setOcupied(int num){
        if(this->isOccupied == 0){
            this->isOccupied = 1;
            this->player = num;
        }
        else{
            this->isOccupied = 2;
            this->player = num;
        }
    }

    vector<vertex*> vertex::getNeighbors(){
        return this->neighbors;
    }

    vector<side*> vertex::getSides(){
        return this->sides;
    }

    void vertex::addNeighbor(vertex* v, side* s){
        this->neighbors.push_back(v);
        this->sides.push_back(s);
        
    }

} // namespace ariel