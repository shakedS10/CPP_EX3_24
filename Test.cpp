#include "doctest.h"
#include "board.hpp"


using namespace std;
using namespace ariel;

TEST_CASE("Vertex tests")
{
    board* b = new board();
    vertex* v = b->getVertex(0);
    CHECK(v->getIsOccupied() == 0);
    CHECK(v->getPlayer() == 0);
    v->setOcupied(1);
    CHECK(v->getIsOccupied() == 1);
    v->setOcupied(1);
    CHECK(v->getIsOccupied() == 2);
    CHECK(v->getPlayer() == 1);
    CHECK(v->getId() == 0);
    CHECK(v->canBuildTown(1) == false);
    CHECK(v->canBuildTown(2) == false);
    CHECK(v->canBuildTown(3) == false);
}


TEST_CASE("Side tests")
{
    board* b = new board();
    side* s;
    for(auto i : b->getSides()){
        if((i->getOwners()[0]->getId() == 0&&i->getOwners()[1]->getId() == 1)||(i->getOwners()[0]->getId() == 1&&i->getOwners()[1]->getId() == 0)){
            s = i;
            break;
        }
    }
    vertex* v1 = s->getOwners()[0];
    v1->setOcupied(1);
    CHECK(s->canBuildRoad(1) == true);
    CHECK(s->getIsOccupied() == false);
    CHECK(s->getPlayer() == 0);
    s->setOcupied(1);
    CHECK(s->getIsOccupied() == true);
    CHECK(s->getId() == 0);
    CHECK(s->canBuildRoad(1) == false);
    CHECK(s->canBuildRoad(2) == false);
    CHECK(s->canBuildRoad(3) == false);
}



TEST_CASE("Board tests"){
    board* b = new board();
    CHECK(b->getTurn() == 1);
    CHECK(b->rollDices() >= 2);
    CHECK(b->rollDices() <= 12);
    CHECK(b->isGameEnd() == 0);
    player* p1 = new player("p1", 1);
    player* p2 = new player("p2", 2);
    player* p3 = new player("p3", 3);
    b->addPlayer(p1);
    b->addPlayer(p2);
    b->addPlayer(p3);
    CHECK(b->checkPlayer(1) == true);
    CHECK(b->checkPlayer(2) == false);
    CHECK(b->checkPlayer(3) == false);
    CHECK(b->checkPlayer(4) == false);
    CHECK(b->checkPlayer(5) == false);
    CHECK(b->checkPlayer(6) == false);
    CHECK(b->getNameFromTurn() == "p1");
    CHECK(b->getPlayerFromTurn() == p1);
    CHECK(b->getVertex(0)->getId() == 0);
    CHECK(b->getVertex(53)->getId() == 53);
    
}


TEST_CASE("Invalid argument tests"){
    board* b = new board();
    CHECK_THROWS(b->getVertex(54));
    CHECK_THROWS(b->getVertex(-1));
    CHECK_THROWS(b->getVertex(100));
    CHECK_THROWS(b->getVertex(-100));
    CHECK_THROWS(b->getVertex(1000));
    CHECK_THROWS(b->getVertex(-1000));
    player* p1 = new player("p1", 1);
    player* p2 = new player("p2", 2);
    player* p3 = new player("p3", 3);
    b->addPlayer(p1);
    b->addPlayer(p2);
    b->addPlayer(p3);
    CHECK_THROWS(p1->firstSettlements(-2, -1 , b));
    CHECK_THROWS(p1->firstSettlements(54, 55 , b));
    CHECK_THROWS(p2->placeRoad(-1, -2, b));

}
