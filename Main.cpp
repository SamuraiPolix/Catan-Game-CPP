/**
 * Main exec file for Ex3.
 *
 */

// FAST START BEGINNING: 1 1 2 3 3 4 4 4 5 16 16 17 18 18 19 22 22 23
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Types.hpp"

using std::exception, std::cout, std::endl, std::vector, std::string, std::cin;
using namespace ariel;

#define NUM_OF_PLAYER 3

void dealWithTrade(Player& currPlayer, Catan& catan);

int main()
{
    Player p1("Amit");      
    Player p2("Yossi");     
    Player p3("Dana");      
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.

    catan.ChooseStartingPlayer();   // should print the name of the starting player
    Board* board = catan.getBoard();
    catan.printBoard();
    size_t choice = 0;
    for (int i = 0; i < 2; i++){        // 2 settlements and 2 roads for each player
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
                try {
                    status = currPlayer.placeSettlement(choice, board);
                } catch (const std::invalid_argument& e){
                    cout << e.what() << endl;
                    status = -1;
                }
                cout << "Status: " << status << endl; // "0" means "success", "-1" means "failure
                if (status == -1){
                    cout << "Please choose another" << endl;
                }
            } while (status == -1);

            cout << "Choose an edge to place a road (enter 2 vertex numbers, seperated by a space!)" << endl;
            do {
                size_t vertex1, vertex2;
                cin >> vertex1;
                while (vertex1 < 0){
                    cout << "Invalid choice" << endl;
                    cin >> vertex1;
                }
                cin >> vertex2;
                while (vertex2 < 0){
                    cout << "Invalid choice" << endl;
                    cin >> vertex2;
                }
                try {
                    status = currPlayer.placeRoad(vertex1, vertex2, board);
                } catch (const std::invalid_argument& e){
                    cout << e.what() << endl;
                    status = -1;
                }
                if (status == -1){
                    cout << "Please choose another" << endl;
                }
            } while (status == -1);
            currPlayer.endTurn(catan);
            catan.printBoard();
        }
    }

    // main game loop
    while (true)
    {
        catan.printBoard();
        Player& currPlayer = catan.getCurrentPlayer();
        cout << "Player " << currPlayer.getName() << " turn" << endl;

        cout << "Choose your action:" << endl;
        cout << "1. Throw cubes" << endl;
        cout << "2. Use development card (You can also use a card after throwing cubes)" << endl;
        cin >> choice;
        if (choice == 1){
            currPlayer.rollDice(catan);
            catan.printPlayers();       // print updated player resources
            int status = -1;
            while (status < 0){
                cout << "Choose your action:" << endl;
                cout << "1. Build a settlement (1 Wood, 1 Brick, 1 Sheep, 1 Wheat)" << endl;
                cout << "2. Build a road (1 Wood, 1 Brick)" << endl;
                cout << "3. Buy a development card (1 Ore, 1 Wheat, 1 Sheep)" << endl;
                cout << "4. Use a development card" << endl;
                cout << "5. Trade" << endl;
                cout << "6. End turn" << endl;
                cin >> choice;
                if (choice == 1){
                    cout << "Choose a vertex to place a settlement" << endl;
                    status = -1;
                    do {
                        cin >> choice;
                        while (choice < 0){
                            cout << "Invalid choice" << endl;
                            cin >> choice;
                        }
                        try {
                            status = currPlayer.placeSettlement(choice, board);
                        } catch (const std::invalid_argument& e){
                            cout << e.what() << endl;
                            status = -1;
                        } catch (const valid_resources& e){
                            cout << e.what() << endl;
                            status = -2;
                        }
                        if (status == -1){
                            cout << "Please choose another" << endl;
                        }
                        else if (status == -2){
                            cout << "Please choose another action" << endl;
                            // goes over loop again
                        }
                    } while (status == -1);
                }
                else if (choice == 2){
                    cout << "Choose an edge to place a road" << endl;
                    status = -1;
                    do {
                        size_t vertex1, vertex2;
                        cin >> vertex1;
                        while (vertex1 < 0){
                            cout << "Invalid choice" << endl;
                            cin >> vertex1;
                        }
                        cin >> vertex2;
                        while (vertex2 < 0){
                            cout << "Invalid choice" << endl;
                            cin >> vertex2;
                        }
                        try {
                            status = currPlayer.placeRoad(vertex1, vertex2, board);
                        } catch (const std::invalid_argument& e){
                            cout << e.what() << endl;
                            status = -1;
                        } catch (const valid_resources& e){
                            cout << e.what() << endl;
                            status = -2;
                        }
                        if (status == -1){
                            cout << "Please choose another" << endl;
                        }
                        else if (status == -2){
                            cout << "Please choose another action" << endl;
                            // goes over loop again
                        }
                    } while (status == -1);
                }
                else if (choice == 3){
                    status = -1;
                    size_t cardIndex = INT16_MAX;
                    try {
                        cardIndex = currPlayer.buyDevelopmentCard(catan);
                    } catch (const std::invalid_argument& e){
                        cout << e.what() << endl;
                        status = -1;
                    } catch (const valid_resources& e){
                        cout << e.what() << endl;
                        status = -2;
                        cout << "Please choose another action" << endl;
                    }
                    cout << "Do you want to use the development card? (1 for yes, 0 for no)" << endl;
                    do {
                        cin >> choice;
                        if (choice == 1){
                            currPlayer.useDevelopmentCard(cardIndex);
                        }
                        if (choice != 0 && choice != 1){
                            cout << "Invalid choice!" << endl;
                        }
                    } while (choice != 0 && choice != 1);
                    
                }
                else if (choice == 4){
                    // TODO REPEATED CODE 1
                    size_t numOfCards = currPlayer.printDevelopmentCards();
                    if (numOfCards == 0){
                        status = -2;
                    }
                    else {
                        cout << "Please choose a card to use (write its number and press enter)" << endl;
                        do {
                            cin >> choice;

                            status = currPlayer.useDevelopmentCard(choice);

                            if (choice >= numOfCards || status == -1){
                                cout << "Please choose another" << endl;
                            }
                        } while (choice >= numOfCards || status == -1);
                    }
                }
                else if (choice == 5){
                    dealWithTrade(currPlayer, catan);
                }
                else if (choice == 6){
                    break;
                }
                else {
                    cout << "Invalid choice" << endl;
                    continue;
                }
                // choice 6 does nothing - goes to end of loop to end turn
            }
        }
        else if (choice == 2){
            int status = -1;
            // TODO REPEATED CODE 1
            size_t numOfCards = currPlayer.printDevelopmentCards();
            if (numOfCards == 0){
                status = -2;
            }
            else {
                cout << "Please choose a card to use (write its number and press enter)" << endl;
                do {
                    cin >> choice;

                    status = currPlayer.useDevelopmentCard(choice);

                    if (choice >= numOfCards || status == -1){
                        cout << "Please choose another" << endl;
                    }
                } while (choice >= numOfCards || status == -1);
            }
            // currPlayer.useDevelopmentCard();
        }
        else {
            cout << "Invalid choice" << endl;
            continue;
        }
        currPlayer.endTurn(catan);

        // check if someone won
        if (catan.printWinner() == 1){
            break;
        }
    }
    return 0;
}

void dealWithTrade(Player& currPlayer, Catan& catan){
    int choice = -1;
    int chosenPlayer = -1;
    do {
        cout << "Choose a player to trade with (enter the number next to the name)" << endl;
        catan.printPlayersExceptCurrent();
        cin >> chosenPlayer;
        // TODO add check for invalid choice (current player or non existing player, usign a function in Catan class)
    } while (chosenPlayer < 0 || chosenPlayer > 2);

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

        size_t amountSend = 0, amountReceive = 0;
        // choose amout of resource to send
        do {
            cout << "Choose the amount of resources to send" << endl;
            cout << "You have " << currPlayer.getResourceAmount((ResourceType)choiceSend)<< " of chosen resource" << endl;
            cin >> amountSend;

            if (amountSend < 1 || amountSend > 5){
                cout << "Invalid choice. Choose again:" << endl;
            }
        } while (amountSend < 1 || amountSend > 5);

        // choose amout of resource to receive
        do {
            cout << "Choose the amount of resources to receive" << endl;
            cout << "They have " << catan.getPlayerById(chosenPlayer).getResourceAmount((ResourceType)choiceReceive)<< " of chosen resource" << endl;
            cin >> choiceReceive;

            if (choiceReceive < 1 || choiceReceive > 5){
                cout << "Invalid choice. Choose again:" << endl;
            }
        } while (choiceReceive < 1 || choiceReceive > 5);
        
        currPlayer.trade(catan.getPlayerById(chosenPlayer), (ResourceType)choiceSend, (ResourceType)choiceReceive, amountSend, amountReceive);
    }
}