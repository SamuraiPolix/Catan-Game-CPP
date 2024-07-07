/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

/*
 * Main exec file for Ex3.
 */

// FAST START BEGINNING: 1 1 2 3 3 4 4 4 5 16 16 17 18 18 19 22 22 23
// FAST START BEGINNING GOOD PLACEMENTS: 30 30 40 32 32 42 34 34 44 23 23 24 18 18 29 41 41 40
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
int useDevelopmentCard(Player& currPlayer, Catan& catan);

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
    for (int i = 0; i < 2; i++){        // 2 settlements and 2 roads for each player
        for (int playerInd = 0; playerInd < NUM_OF_PLAYER; playerInd++){
            Player& currPlayer = catan.getCurrentPlayer();
            cout << "Player " << currPlayer.getName() << " turn" << endl;
            cout << "Choose a vertex to place a settlement" << endl;
            int status = -1;
            do {
                size_t vertexChoice = 0;
                cin >> vertexChoice;
                while (vertexChoice < 0){
                    cout << "Invalid vertex choice" << endl;
                    cin >> vertexChoice;
                }
                try {
                    status = currPlayer.placeSettlement(vertexChoice, board);
                } catch (const std::invalid_argument& e){
                    cout << e.what() << endl;
                    status = -1;
                    cout << "Please choose another vertex" << endl;
                }
            } while (status == -1);

            cout << "Choose an edge to place a road (enter 2 vertex numbers, seperated by a space!)" << endl;
            do {
                size_t vertex1, vertex2;
                cin >> vertex1;
                while (vertex1 < 0){
                    cout << "Invalid vertex choice" << endl;
                    cin >> vertex1;
                }
                cin >> vertex2;
                while (vertex2 < 0){
                    cout << "Invalid vertex choice" << endl;
                    cin >> vertex2;
                }
                try {
                    status = currPlayer.placeRoad(vertex1, vertex2, board);
                } catch (const std::invalid_argument& e){
                    cout << e.what() << endl;
                    status = -1;
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
        int status1 = -1;
        int firstMenuChoice = -1;
        while (status1 < 0) {
            cout << "Choose your action:" << endl;
            cout << "1. Throw cubes" << endl;
            cout << "2. Use development card (You can also use a card after throwing cubes)" << endl;
            cin >> firstMenuChoice;
            if (firstMenuChoice == 1){
                currPlayer.rollDice(catan);
                int status = -1;
                int secondMenuChoice = -1;
                while (status < 0 || secondMenuChoice != 6){
                    catan.printPlayers();       // print updated player resources
                    cout << "Choose your action:" << endl;
                    cout << "1. Build a settlement (1 Wood, 1 Brick, 1 Sheep, 1 Wheat)" << endl;
                    cout << "2. Build a road (1 Wood, 1 Brick)" << endl;
                    cout << "3. Buy a development card (1 Ore, 1 Wheat, 1 Sheep)" << endl;
                    cout << "4. Use a development card" << endl;
                    cout << "5. Trade" << endl;
                    cout << "6. End turn" << endl;
                    cin >> secondMenuChoice;
                    if (secondMenuChoice == 1){
                        if (currPlayer.availableResourcesBuildable(BuildableTypes::Settlement) == false){
                            cout << "You don't have enough resources to build a settlement, choose another action" << endl;
                            continue;
                        }
                        cout << "Choose a vertex to place a settlement" << endl;
                        status = -1;
                        size_t vertexChoice = 0;
                        do {
                            cin >> vertexChoice;
                            while (vertexChoice < 0){
                                cout << "Invalid choice" << endl;
                                cin >> vertexChoice;
                            }
                            try {
                                status = currPlayer.placeSettlement(vertexChoice, board);
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
                    else if (secondMenuChoice == 2){
                        if (currPlayer.availableResourcesBuildable(BuildableTypes::Road) == false){
                            cout << "You don't have enough resources to build a road, choose another action" << endl;
                            continue;
                        }
                        cout << "Choose an edge to place a road" << endl;
                        status = -1;
                        do {
                            size_t vertex1, vertex2;
                            cin >> vertex1;
                            while (vertex1 < 0){
                                cout << "Invalid vertex choice" << endl;
                                cin >> vertex1;
                            }
                            cin >> vertex2;
                            while (vertex2 < 0){
                                cout << "Invalid vertex choice" << endl;
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
                    else if (secondMenuChoice == 3){
                        if (currPlayer.availableResourcesDevelopmentCard() == false){
                            cout << "You don't have enough resources to buy a development card, choose another action" << endl;
                            continue;
                        }
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
                        int useCard = -1;
                        do {
                            cin >> useCard;
                            if (useCard == 1){
                                currPlayer.useDevelopmentCard(cardIndex);
                            }
                            if (useCard != 0 && useCard != 1){
                                cout << "Invalid choice!" << endl;
                            }
                        } while (useCard != 0 && useCard != 1);
                        
                    }
                    else if (secondMenuChoice == 4){
                        status = useDevelopmentCard(currPlayer, catan);
                    }
                    else if (secondMenuChoice == 5){
                        dealWithTrade(currPlayer, catan);
                    }
                    else if (secondMenuChoice == 6){
                        break;      // go to end of loop to end turn
                    }
                    else {
                        cout << "Invalid choice" << endl;
                        continue;
                    }
                }
                if (secondMenuChoice == 6){
                    break;
                }
            }
            else if (firstMenuChoice == 2){
                status1 = useDevelopmentCard(currPlayer, catan);
            }
            else {
                cout << "Invalid choice" << endl;
                continue;
            }
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
    int chosenPlayer = -1;
    do {
        cout << currPlayer.getName() << "choose a player to trade with (enter the number next to the name)" << endl;
        catan.printPlayersExceptCurrent();
        cin >> chosenPlayer;
        // TODO add check for invalid choice (current player or non existing player, usign a function in Catan class)
    } while (chosenPlayer < 0 || chosenPlayer > 2);

    vector<tuple<ResourceType, size_t>> sendingResources;
    vector<tuple<ResourceType, size_t>> receivingResources;

    int choiceSend = -1, choiceReceive = -1;
    size_t amountSend = 0, amountReceive = 0;
    int chooseAnother = -1;
    // choose a resource to send
    do {
        do {
            cout << "Choose a resource to send" << endl;
            cout << "0. None" << endl;
            cout << "1. Ore" << " (" << currPlayer.getResourceAmount(ResourceType::Ore) << " available)" << endl;
            cout << "2. Wheat" << " (" << currPlayer.getResourceAmount(ResourceType::Wheat) << " available)" << endl;
            cout << "3. Sheep" << " (" << currPlayer.getResourceAmount(ResourceType::Sheep) << " available)" << endl;
            cout << "4. Wood" << " (" << currPlayer.getResourceAmount(ResourceType::Wood) << " available)" << endl;
            cout << "5. Brick" << " (" << currPlayer.getResourceAmount(ResourceType::Brick) << " available)" << endl;
            cin >> choiceSend;
            if (choiceSend < 0 || choiceSend > 5){
                cout << "Invalid choice. Choose again:" << endl;
            }
            if (choiceSend != 0 && currPlayer.getResourceAmount((ResourceType)choiceSend) == 0){
                cout << "You don't have any of this resource. Choose again:" << endl;
                choiceSend = -1;
            }
        } while (choiceSend < 0 || choiceSend > 5);


        // choose amout of resource to send
        while (choiceSend != 0 && (amountSend < 1 || amountSend > currPlayer.getResourceAmount((ResourceType)choiceSend))) {
            cout << "Choose the amount of selected resource to send" << endl;
            cout << "You have " << currPlayer.getResourceAmount((ResourceType)choiceSend)<< " of chosen resource" << endl;
            cin >> amountSend;

            if (amountSend < 1 || amountSend > currPlayer.getResourceAmount((ResourceType)choiceSend)){
                cout << "Invalid amount. Choose again:" << endl;
            }
        }
        sendingResources.push_back(std::make_tuple((ResourceType)choiceSend, amountSend));
        chooseAnother = -1;
        if (choiceSend != 0){
            cout << "Do you want to choose another resource to send? (1 for yes, 0 for no)" << endl;
            cin >> chooseAnother;
            while (chooseAnother != 0 && chooseAnother != 1){
                cout << "Invalid choice. Choose again:" << endl;
                cin >> chooseAnother;
            }
        }
        amountSend = 0;
        choiceSend = -1;
    } while (chooseAnother == 1);

    chooseAnother = -1;

    // choose a resource to receive
    do {
        do {
            cout << "Choose a resource to receive" << endl;
            cout << "0. None" << endl;
            cout << "1. Ore" << " (" << catan.getPlayerById(chosenPlayer).getResourceAmount(ResourceType::Ore) << " available)" << endl;
            cout << "2. Wheat" << " (" << catan.getPlayerById(chosenPlayer).getResourceAmount(ResourceType::Wheat) << " available)" << endl;
            cout << "3. Sheep" << " (" << catan.getPlayerById(chosenPlayer).getResourceAmount(ResourceType::Sheep) << " available)" << endl;
            cout << "4. Wood" << " (" << catan.getPlayerById(chosenPlayer).getResourceAmount(ResourceType::Wood) << " available)" << endl;
            cout << "5. Brick" << " (" << catan.getPlayerById(chosenPlayer).getResourceAmount(ResourceType::Brick) << " available)" << endl;
            cin >> choiceReceive;
            if (choiceReceive < 0 || choiceReceive > 5){
                cout << "Invalid choice. Choose again:" << endl;
            }
            if (choiceReceive != 0 && catan.getPlayerById(chosenPlayer).getResourceAmount((ResourceType)choiceReceive) == 0){
                cout << "They don't have any of this resource. Choose again:" << endl;
                choiceReceive = -1;
            }
        } while (choiceReceive < 0 || choiceReceive > 5);

        // choose amount of resource to receive
        while (choiceReceive != 0 && (amountReceive < 1 || amountReceive > catan.getPlayerById(chosenPlayer).getResourceAmount((ResourceType)choiceReceive))) {
            cout << "Choose the amount of resources to receive" << endl;
            cout << "They have " << catan.getPlayerById(chosenPlayer).getResourceAmount((ResourceType)choiceReceive)<< " of chosen resource" << endl;
            cin >> amountReceive;

            if (amountReceive < 1 || amountReceive > catan.getPlayerById(chosenPlayer).getResourceAmount((ResourceType)choiceReceive)){
                cout << "Invalid amount. Choose again:" << endl;
            }
        } 
        receivingResources.push_back(std::make_tuple((ResourceType)choiceReceive, amountReceive));
        chooseAnother = -1;
        if (choiceReceive != 0){
            cout << "Do you want to choose another resource to receive? (1 for yes, 0 for no)" << endl;
            cin >> chooseAnother;
            while (chooseAnother != 0 && chooseAnother != 1){
                cout << "Invalid choice. Choose again:" << endl;
                cin >> chooseAnother;
            }
        }
        amountReceive = 0;
        choiceReceive = -1;
    } while (chooseAnother == 1);
    // currPlayer.trade(catan.getPlayerById(chosenPlayer), (ResourceType)choiceSend, (ResourceType)choiceReceive, amountSend, amountReceive);
    currPlayer.trade(catan.getPlayerById(chosenPlayer), sendingResources, receivingResources);
}

int useDevelopmentCard(Player& currPlayer, Catan& catan){
    cout << endl;
    size_t numOfCards = currPlayer.printDevelopmentCards();
    if (numOfCards == 0){
        cout << "You don't have any development cards, choose another action!" << endl;
        return -2;
    }
    size_t cardChoice = 0;
    cout << "Please choose a card to use (write its number and press enter) or -1 to cancel:" << endl;
    do {
        cin >> cardChoice;
        if (cardChoice == -1){
            return -1;
        }
        if (cardChoice >= numOfCards){
            cout << "Please choose another " << endl;
        }
    } while (cardChoice >= numOfCards);
    currPlayer.useDevelopmentCard(cardChoice);
    return 1;
}