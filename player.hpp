#include <iostream>



using namespace std;

namespace ariel
{
    class Player
    {
    private:
        string name;
        int wood;
        int bricks;
        int wheat;
        int ore;
        int wool;

    public:
        Player(string name);
        void placeSettelemnt(vector<string> places, vector<int> placesNum, Board board);
        void placeRoad(vector<string> places, vector<int> placesNum, Board board);
        void rollDice();
    };
} // namespace ariel