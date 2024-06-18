#include "hexagon.hpp"

using namespace std;

namespace ariel{
    hexagon::hexagon(int num){
        this->num = num;
        this->vertices = vector<vertex*>();
        this->sides = vector<side*>();
    }

    vector<vertex*> hexagon::getV(){
        return this->vertices;
    }

    vector<side*> hexagon::getS(){
        return this->sides;
    }

    void hexagon::addV(vertex* v){
        this->vertices.push_back(v);
    }

    void hexagon::addS(side* s){
        this->sides.push_back(s);
    }


} // namespace ariel


