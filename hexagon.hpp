#pragma once

#include <iostream>
#include "playernum.hpp"
#include "vertex.hpp"
#include "side.hpp"
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

    };

} // namespace ariel