/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

/*
 * Demo file for Ex3.
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"

using std::exception, std::cout, std::endl, std::vector, std::string;
using namespace ariel;

#define NUM_OF_PLAYER 3

int main()
{
    const size_t numbers[18] = {29, 29, 30, 20, 20, 21, 33, 33, 34, 24, 24, 25, 10, 10, 9, 41, 41, 42};
    size_t index = 0;
    
    // Create players
    Player p1("Sam");
    Player p2("Benjamin");
    Player p3("Dana");

    // Create Catan game
    Catan catan(p1, p2, p3);

    // Get Board
    Board* board = catan.getBoard();

    // Choose starting player
    catan.ChooseStartingPlayer(0);  // should print the name of the starting player, set to Sam for demo purposes.

    // Print board and players
    catan.printBoard();

    // Place first settlements and roads
    p1.placeSettlement(29, board);
    p1.placeRoad(29, 30, board);

    p1.endTurn(catan);
    catan.printBoard();

    p2.placeSettlement(20, board);
    p2.placeRoad(20, 21, board);

    p2.endTurn(catan);
    catan.printBoard();

    p3.placeSettlement(33, board);
    p3.placeRoad(33, 34, board);

    p3.endTurn(catan);
    catan.printBoard();

    p1.placeSettlement(24, board);
    p1.placeRoad(24, 25, board);

    p1.endTurn(catan);
    catan.printBoard();

    // p2 tries to place a settlement in the same location as p1 - should throw exception
    try {
        p2.placeSettlement(24, board);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    // good placement
    p2.placeSettlement(10, board);

    // p2 tries to place a road in the same location as p1 - should throw exception
    try {
        p2.placeRoad(24, 25, board);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    // p2 tries to place a road not connected to his settlement - should throw exception
    try {
        p2.placeRoad(0, 1, board);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    // good placement
    p2.placeRoad(10, 9, board);

    p2.endTurn(catan);
    catan.printBoard();

    // p1 tries to place a settlement on another player's turn - should throw exception
    try {
        p1.placeSettlement(20, board);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    p3.placeSettlement(41, board);
    p3.placeRoad(41, 42, board);

    p3.endTurn(catan);
    catan.printBoard();

    // p1 turn
    p1.rollDice(catan);
    p1.buyDevelopmentCard(catan);
    p1.endTurn(catan);

    catan.printBoard();


    // p2 turn
    p2.rollDice(catan);
    p2.endTurn(catan);

    catan.printBoard();


    // p3 turn
    p3.rollDice(catan);
    p3.endTurn(catan);

    catan.printBoard();


    // p2 tries to roll the dice again, but it's not his turn - should throw exception
    try {
        p2.rollDice(catan);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    // p1 turn
    p1.rollDice(catan);
    catan.printPlayers();
    cout << "TRADE" << endl;
    p1.trade(p2, ResourceType::Brick, ResourceType::Wood, 1, 1);
    p1.endTurn(catan);

    catan.printPlayers();

    // p2 turn
    p2.rollDice(catan);
    // p2 tries to trade with p1, but doesn't have enough resources - should throw exception
    try{
        p2.buyDevelopmentCard(catan);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    p2.endTurn(catan);

    p1.printPoints();
    p2.printPoints();
    p3.printPoints();

    catan.printBoard();
    
    catan.printWinner(); // Should print None because no player reached 10 points.

    // Print winner
    cout << "Winner is: " << catan.printWinner() << endl;

    return 0;    
}