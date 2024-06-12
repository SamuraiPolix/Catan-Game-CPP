/**
 * Main exec file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "ResourceTypes.hpp"

using std::exception, std::cout, std::endl, std::vector, std::string;
using namespace ariel;

#define NUM_OF_PLAYER 3

int main()
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.

    catan.ChooseStartingPlayer();   // should print the name of the starting player
    
    size_t choice = -1;
    for (int playerInd = 0; playerInd < NUM_OF_PLAYER; playerInd++){
        Player& currPlayer = catan.getCurrentPlayer();
        cout << "Player " << currPlayer.getName() << " turn" << endl;
        cout << "Choose a vertex to place a settlement" << endl;
        int status = -1;
        do {
            cin >> choice;
            while (choice < 0){
                cout << "Invalid choice" << endl;
                cin >> choice;
            }
            status = p1.placeSettlement(choice, catan);
            if (status == -1){
                cout << "Please choose another" << endl;
            }
        } while (status == -1);

        cout << "Choose an edge to place a road" << endl;
        do {
            cin >> choice;
            while (choice < 0){
                cout << "Invalid choice" << endl;
                cin >> choice;
            }
            status = p1.placeRoad(choice, catan);
            if (status == -1){
                cout << "Please choose another" << endl;
            }
        } while (status == -1);
        currPlayer.endTurn(catan);
    }

    while (true)
    {
        Player& currPlayer = catan.getCurrentPlayer();
        cout << "Player " << currPlayer.getName() << " turn" << endl;

        cout << "Choose your action:" << endl;
        cout << "1. Throw cubes" << endl;
        cout << "2. Use development card" << endl;
        cin >> choice;
        if (choice == 1){
            currPlayer.rollDice();
            cout << "Choose your action:" << endl;
            cout << "1. Build a settlement" << endl;
            cout << "2. Build a road" << endl;
            cout << "3. Buy a development card" << endl;
            cout << "4. Trade" << endl;
            cin >> choice;
            if (choice == 1){
                cout << "Choose a vertex to place a settlement" << endl;
                int status = -1;
                do {
                    cin >> choice;
                    while (choice < 0){
                        cout << "Invalid choice" << endl;
                        cin >> choice;
                    }
                    status = p1.placeSettlement(choice, catan);
                    if (status == -1){
                        cout << "Please choose another" << endl;
                    }
                } while (status == -1);
            }
            else if (choice == 2){
                cout << "Choose an edge to place a road" << endl;
                int status = -1;
                do {
                    cin >> choice;
                    while (choice < 0){
                        cout << "Invalid choice" << endl;
                        cin >> choice;
                    }
                    status = p1.placeRoad(choice, catan);
                    if (status == -1){
                        cout << "Please choose another" << endl;
                    }
                } while (status == -1);
            }
            else if (choice == 3){
                currPlayer.buyDevelopmentCard();
            }
            else if (choice == 4){
                dealWithTrade(currPlayer);
            }
        }
        else if (choice == 2){
            currPlayer.useDevelopmentCard();
        }
        else {
            cout << "Invalid choice" << endl;
            continue;
        }
        currPlayer.endTurn(catan);
    }
    return 0;
}

void dealWithTrade(Player& currPlayer){
    do {
        cout << "Choose a player to trade with (enter the number next to the name)" << endl;
        catan.printPlayersExceptCurrent();
        int choice = -1;
        cin >> choice;
        // TODO add check for invalid choice (current player or non existing player, usign a function in Catan class)
    } while (choice < 0 || choice > 2);

    if (choice == 1){
        // choose a resource to send
        int choiceSend = -1, choiceReceive = -1;
        do {
            cout << "Choose a resource to send" << endl;
            cout << "1. Ore" << endl;
            cout << "2. Wheat" << endl;
            cout << "3. Sheep" << endl;
            cout << "4. Wood" << endl;
            cout << "5. Brick" << endl;
            cin >> choiceSend;
            if (choiceSend < 1 || choiceSend > 5){
                cout << "Invalid choice. Choose again:" << endl;
            }
        } while (choiceSend < 1 || choiceSend > 5);

        // choose a resource to receive
        do {
            cout << "Choose a resource to receive" << endl;
            cout << "1. Ore" << endl;
            cout << "2. Wheat" << endl;
            cout << "3. Sheep" << endl;
            cout << "4. Wood" << endl;
            cout << "5. Brick" << endl;
            cin >> choiceReceive;
            if (choiceReceive < 1 || choiceReceive > 5){
                cout << "Invalid choice. Choose again:" << endl;
            }
        } while (choiceReceive < 1 || choiceReceive > 5);

        int amountSend = -1, amountReceive = -1;
        // choose amout of resource to send
        do {
            cout << "Choose the amount of resources to send" << endl;
            cout << "You have " << currPlayer.getResourceAmount(choiceSend)<< " of chosen resource" << endl;
            cin >> amountSend;

            if (amountSend < 1 || amountSend > 5){
                cout << "Invalid choice. Choose again:" << endl;
            }
        } while (amountSend < 1 || amountSend > 5);

        // choose amout of resource to receive
        do {
            cout << "Choose the amount of resources to receive" << endl;
            cout << "They have " << catan.getPlayerByName().getResourceAmount(choiceReceive)<< " of chosen resource" << endl;
            cin >> choiceReceive;

            if (choiceReceive < 1 || choiceReceive > 5){
                cout << "Invalid choice. Choose again:" << endl;
            }
        } while (choiceReceive < 1 || choiceReceive > 5);
        
        currPlayer.trade(p2, choiceSend, choiceReceive, amountSend, amountReceive);
    }
}