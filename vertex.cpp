#include "vertex.hpp"
using namespace std;

namespace ariel{
    vertex::vertex(int id){
        this->isOccupied = 0;
        this->id = id;
        this->player = 0;
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

    bool vertex::canBuildTown(int num){
       bool canBuild = false;
       for (auto s : this->sides){
           if(s->getPlayer() == num){
               canBuild = true;
           }
       }
        if(canBuild == true){
            for (auto v : this->neighbors){
                if(v->getPlayer() != 0){
                    cout << "v->getPlayer(): " << v->getPlayer() << endl;
                    canBuild = false;
                }
            }
        }
        return canBuild;
          
    }

} // namespace ariel