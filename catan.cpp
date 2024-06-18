#include <iostream>
#include <vector>
#include <string>
#include "board.hpp"


using namespace std;
using namespace ariel;

int main(){
    board* b = new board();
    b->printBoard();
    return 0;
}