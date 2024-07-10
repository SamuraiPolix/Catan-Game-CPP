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
    p1.placeSettlement(30, board);
    p1.placeRoad(30, 40, board);

    catan.printBoard();

    p2.placeSettlement(32, board);
    p2.placeRoad(32, 42, board);

    catan.printBoard();

    p3.placeSettlement(34, board);
    p3.placeRoad(34, 44, board);

    catan.printBoard();

    p1.placeSettlement(23, board);
    p1.placeRoad(23, 24, board);

    catan.printBoard();

    // p2 tries to place a settlement in the same location as p1 - should throw exception
    try {
        p2.placeSettlement(23, board);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    // good placement
    p2.placeSettlement(18, board);

    // p2 tries to place a road in the same location as p1 - should throw exception
    try {
        p2.placeRoad(23, 24, board);
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
    p2.placeRoad(18, 29, board);

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
    p3.placeRoad(41, 40, board);

    catan.printBoard();

    // p1 turn
    p1.rollDice(catan);
    p1.placeRoad(30, 31, board);
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
    p1.trade(p2, ResourceType::Wood, ResourceType::Brick, 1, 1);
    p1.endTurn(catan);

    catan.printPlayers();

    // p2 turn
    p2.rollDice(catan);
    p2.buyDevelopmentCard(catan);
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