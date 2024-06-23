#pragma once

#include <iostream>
#include "vertex.hpp"
#include "side.hpp"
#include "player.hpp"
#include <vector>

using namespace std;

namespace ariel{
class vertex;
class side;
    class hexagon
    {
    private:
        // side bright;
        // side right;
        // side left;
        // side blight;
        // side tleft;
        // side tright;
        // vertex top;
        // vertex bottom;
        // vertex vbright;
        // vertex vbleft;
        // vertex vtright;
        // vertex vtleft;
        // int hexagonNum;
        vector<vertex*> vertices = vector<vertex*>();
        vector<side*> sides = vector<side*>();
        int num;
        string type;
    public:
        hexagon(int num);
        vector<vertex*> getV();
        vector<side*> getS();
        
        void addV(vertex* v);
        void addS(side* s);
        int getNum(){
            return this->num;}
        vertex* getVertex(int i){
            return this->vertices[i-1];
        }
        side* getSide(int i){
            return this->sides[i];
        }
        void setType(string type){
            this->type = type;
        }
        string getType(){
            return this->type;
        }

    };

} // namespace ariel