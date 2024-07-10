/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Catan.hpp"
#include "Player.hpp"
#include "Types.hpp"
#include "Board.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using std::cout, std::endl, std::vector, std::string, std::rand, std::srand, std::time, std::shuffle, std::default_random_engine, std::invalid_argument, std::cin;
using namespace ariel;

// starting positions for settlements and roads
static const size_t numbers[18] = {29, 29, 30, 20, 20, 21, 33, 33, 34, 24, 24, 25, 10, 10, 9, 41, 41, 42};
size_t setupIndex = 0;

TEST_CASE("Test Catan turn order") {
    Player p1("Sam");
    Player p2("John");
    Player p3("Jane");
    ariel::Catan game(p1, p2, p3);
    game.ChooseStartingPlayer(0);
    CHECK(game.getCurrentPlayer().getSimpleName() == "Sam");
    game.nextPlayer();
    CHECK(game.getCurrentPlayer().getSimpleName() == "John");
    game.nextPlayer();
    CHECK(game.getCurrentPlayer().getSimpleName() == "Jane");
    game.nextPlayer();
    CHECK(game.getCurrentPlayer().getSimpleName() == "Sam");
}

TEST_CASE("Test Catan giveResources") {
    Player p1("Sam");
    Player p2("John");
    Player p3("Jane");
    ariel::Catan game(p1, p2, p3);
    game.ChooseStartingPlayer(0);

    // make sure everyone starts with 0 resources
    for (Player* player : game.getPlayers()) {
        CHECK(player->numOfResources() == 0);
    }
    // amounts shouldnt change because no settlements
    game.giveResources(2);
    for (int i = 3; i < 6+6; i++) {
        if (i == 7) continue;
        game.giveResources(i);      // roll everything except 7
    }
    for (Player* player : game.getPlayers()) {
        CHECK(player->numOfResources() == 0);
    }

    // set each player with 1 settlement and road - still no change in resources if no rolls (second settlment gives starting resources)
    setupIndex = 0;
    Player* player;
    for (int i = 0; i < 3; i++) {
        player = &game.getCurrentPlayer();
        player->placeSettlement(numbers[setupIndex], game.getBoard());
        setupIndex++;
        player->placeRoad(numbers[setupIndex], numbers[setupIndex+1], game.getBoard());
        setupIndex += 2;
        player->endTurn(game);
    }

    for (Player* player : game.getPlayers()) {
        CHECK(player->numOfResources() == 0);
    }

    // set second settlement for each player
    for (int i = 0; i < 3; i++) {
        player = &game.getCurrentPlayer();
        player->placeSettlement(numbers[setupIndex], game.getBoard());
        setupIndex++;
        player->placeRoad(numbers[setupIndex], numbers[setupIndex+1], game.getBoard());
        setupIndex += 2;
        player->endTurn(game);
    }


    for (Player* player : game.getPlayers()) {
        cout << player->getSimpleName() << " has " << player->numOfResources() << " resources" << endl;
        CHECK(player->numOfResources() != 0);
    }




    
}