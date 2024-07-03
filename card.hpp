#pragma once
#include <iostream>
#include <vector>
#include <string>


using namespace std;


namespace ariel
{

    class card
    {
    private:
        int type; // 0 - knight , 1 - victory point , 2 - year of plenty, 3 - biggest army, 4 - monopoly , 5 - road building
    
    public:
        card(int type);
        int getType(){
            return this->type;
        }
    };


    class yearOfPlenty : public card
    {
        public:
        yearOfPlenty() : card(2){}
    };

    class monopolycard : public card
    {
        public:
        monopolycard() : card(4){}
    };

    class roadBuilding : public card
    {
        public:
        roadBuilding() : card(5){}
    };


    class knight : public card
    {
        public:
        knight() : card(0){}
    };

    class victoryPoint : public card
    {
        public:
        victoryPoint() : card(1){}
    };

    class biggestArmy : public card
    {
        public:
        biggestArmy() : card(3){}
    };

    class longestRoad : public card
    {
        public:
        longestRoad() : card(4){}
    };





    

}