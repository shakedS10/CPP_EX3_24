#include <iostream>
#include <vector>
#include <string>
#include "player.hpp"
#include "board.hpp"



using namespace std;
using namespace ariel;

int main(){
    board* b = new board();
    b->printBoard();
    player* p1 = new player("p1", 1);
    p1->addResource("wood", 2);
    p1->addResource("bricks", 2);
    player* p2 = new player("p2", 2);
    p2->addResource("wood", 2);
    p2->addResource("bricks", 2);
    player* p3 = new player("p3", 3);
    p3->addResource("wood", 2);
    p3->addResource("bricks", 2);
    b->addPlayer(p1);
    b->addPlayer(p2);
    b->addPlayer(p3);
    p1->firstSettlements(0, 30 , b);
    b->printBoard();
    p1->placeRoad(0, 1, b);
    p1->placeRoad(30,29,b);
    b->printBoard();
    b->nextTurn();
    p2->firstSettlements(8, 37 , b);
    b->printBoard();
    p2->placeRoad(8, 9, b);
    p2->placeRoad(37, 45, b);
    b->printBoard();
    b->nextTurn();
    p3->firstSettlements(16, 50 , b);
    b->printBoard();
    p3->placeRoad(16, 17, b);
    p3->placeRoad(50, 51, b);
    b->printBoard();
    b->nextTurn();
    p1->addResource("wood", 10);
    p1->addResource("bricks", 10);
    p1->addResource("wheat", 10);
    p1->addResource("ore", 10);
    p1->addResource("wool", 10);
    p1->printResources();
    // for(int i = 1; i < 4; i++){
    //     cout << b->getNameFromTurn() << " it's your turn" << endl;
    //     cout << "First settlements" << endl;
    //     int v1, v2;
    //     cin >> v1 >> v2;
    //     cout << "Placing settlement on vertex " << v1 << endl;
    //     cout << "Placing settlement on vertex " << v2 << endl;
    //     b->getPlayerFromTurn()->firstSettlements(v1, v2, b);
    //     b->printBoard();
    //     cout << "choose first road" << endl;
    //     int r1, r2;
    //     cin >> r1 >> r2;
    //     b->getPlayerFromTurn()->placeRoad(r1, r2, b);
    //     cout << "choose second road" << endl;
    //     cin >> r1 >> r2;
    //     b->getPlayerFromTurn()->placeRoad(r1, r2, b);
    //     b->printBoard();
    //     b->nextTurn();
    // }
    char trade = ' ';
    while (b->isGameEnd()==0){
        if(trade == ' '){
            b->printBoard();
            cout <<  b->getNameFromTurn() <<" it's your turn" << endl;
            cout << "Rolling dices" << endl;
            b->getPlayerFromTurn()->rollDice(b);
            cout << "want to buy a card? y/n" << endl;
            char buy;
            cin >> buy;
            if(buy == 'y'){
                b->getPlayerFromTurn()->buyCard(b);

            }
        }
        while(trade != 'n'){
            cout << "do you want to trade? y/n" << endl;
            cin >> trade;
            if(trade == 'y'){
                cout << "Choose player to trade with" << endl;
                string player;
                cin >> player;
                b->getPlayerFromTurn()->trade(b->getPlayerByName(player));
            }
        }
        cout << "Choose your move : 's' for settlement, 'r' for road, 'n' for no move/next turn, 'i' show items, 'v' show victory points, c show cards, 'u' to use card " << endl;
        char move;
        cin >> move;
        switch (move)
        {
            case 's':
                cout << "Choose vertex for settlement" << endl;
                int v;
                cin >> v;
                b->getPlayerFromTurn()->placeSettlement(v, b);
                break;
            case 'r':
                cout << "Choose vertices for road" << endl;
                int v1, v2;
                cin >> v1 >> v2;
                b->getPlayerFromTurn()->placeRoad(v1, v2, b);
                break;
            case 'n':
                b->nextTurn();
                trade = ' ';
                break;
            case 'i':
                b->getPlayerFromTurn()->printResources();
                break;
            case 'v':
                cout << "Victory points: " << b->getPlayerFromTurn()->getVictoryPoints() << endl;
                break;
            case 'c':
                b->getPlayerFromTurn()->showCards();
                break;
            case 'u':
                b->getPlayerFromTurn()->showCards();
                cout << "Choose card to use" << endl;
                int i;
                cin >> i;
                b->getPlayerFromTurn()->useCard(i, b);
                break;
        }
        if(b->isGameEnd()!=0){
            cout << b->getNameFromTurn() << " won the game" << endl;
            break;
        }
        
    }



    return 0;
}