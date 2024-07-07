/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

#include "Catan.hpp"
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "Types.hpp"

using std::cout, std::endl, std::rand, std::srand, std::time, std::shuffle, std::default_random_engine, std::invalid_argument, std::cin;
namespace ariel {
    Catan::Catan(Player& p1, Player& p2, Player& p3) {
        board = new Board();
        this->players.push_back(&p1);
        this->players.push_back(&p2);
        this->players.push_back(&p3);
        this->players.shrink_to_fit();
        // this->developmentCards = vector<DevelopmentCard*>(25, NULL);
        // Changed num of cards to match assignment requirements
        this->developmentCards = vector<DevelopmentCard*>(13, NULL);

        initCards();
    }
    Catan::~Catan(){
        delete board;
    }

    // this functions generates a random player and prints its name
    void Catan::ChooseStartingPlayer(){
        srand(time(0));
        this->currPlayer = rand() % 3;
        std::cout << "The starting player is: " << this->getCurrentPlayer().getName() << std::endl;
        getCurrentPlayer().startTurn();
    }

    void Catan::ChooseStartingPlayer(size_t index){
        this->currPlayer = index;
        std::cout << "The starting player is: " << this->getCurrentPlayer().getName() << std::endl;
        getCurrentPlayer().startTurn();
    }

    // returns the current playing player
    Player& Catan::getCurrentPlayer(){
        return *this->players[(size_t)this->currPlayer];
    }

    Board* Catan::getBoard(){
        return this->board;
    }
    void Catan::nextPlayer(){
        this->currPlayer = (this->currPlayer + 1) % 3;
        getCurrentPlayer().startTurn();
    }
    void Catan::printPlayersExceptCurrent(){
        for (size_t i = 0; i < players.size(); i++){
            if (i != this->currPlayer){
                cout << i << ". " << this->players[i]->getName() << endl;
            }
        }
    }
    vector<Player*> Catan::getPlayers(){
        return this->players;
    }

    void Catan::initCards(){
        // In the base game, there are 25 development cards: 14 knight cards, 5 victory point cards, 2 road building, 2 year of plenty, and 2 monopoly. 
        // Source: https://catan.fandom.com/wiki/Development_card
        // TODO change num of Knight cards to 3 to match assignment requirements, VictoryPoints to 4 - total of 13 cards    
        for (int i = 0; i < 3; i++){
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::Knight, this));
        }
        for (int i = 0; i < 4; i++){
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::VictoryPoint, this));
        }
        for (int i = 0; i < 2; i++){
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::RoadBuilding, this));
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::YearOfPlenty, this));
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::Monopoly, this));
        }

        developmentCards.shrink_to_fit();

        // shuffle the cards
        shuffle(developmentCards.begin(), developmentCards.end(), default_random_engine(0));
    }

    // returns the index of the development card
    size_t Catan::addDevelopmentCard(Player& player){
        // add development card
        size_t indexForPlayer = player.addDevelopmentCard(*developmentCards.back());
        developmentCards.back()->setOwner(&player);
        if (developmentCards.back()->getType() == CardType::VictoryPoint){
            player.addVictoryPoints(1);
        }
        if (developmentCards.back()->getType() == CardType::Knight){
            player.updateLargestArmy();
        }
        // print the card
        cout << "Player " << player.getName() << " bought a development card" << endl;
        cout << "The card is: " << *developmentCards.back() << endl;
        developmentCards.pop_back();
        return indexForPlayer;
    }

    void Catan::giveResources(int diceRoll){
        for (size_t i = 0; i < players.size(); i++){
            vector<Tile>& playerTiles = players[i]->getTiles();
            for (size_t j = 0; j < playerTiles.size(); j++){
                if (playerTiles[j].getNumber() == diceRoll){
                    ResourceType resource = playerTiles[j].getResource();
                    players[i]->addResource(resource, 1);
                    cout << "Player " << players[i]->getName() << " got 1 " << getResourceName(resource) << " from tile (" << playerTiles[j].getX() << ", " << playerTiles[j].getY() << ")" << endl;
                }
            }
        }
    }

    void Catan::printBoard(){
        printPlayers();
        board->printBoard();
    }

    void Catan::printPlayers(){
        for (size_t i = 0; i < players.size(); i++){
            cout << "Player #" << i << " " << *players[i] << endl;
        }
    }

    void Catan::rolledSeven(){
        // each player with more than 7 resources must return half of them to the bank
        cout << "7 was rolled! Players with more than 7 resources must return half of them to the bank" << endl;
        int count = 0;
        for (size_t i = 0; i < players.size(); i++){
            if (players[i]->numOfResources() > 7){
                count++;
                cout << "Player " << players[i]->getName() << " has more than 7 resources" << endl;
                cout << *players[i] << endl;
                cout << players[i]->getName() << ", choose half of your resources (" << players[i]->numOfResources()/2 << ") to return to the bank" << endl;
                cout << "Write your choices in the following format: <resource> <amount> <resource> <amount> ..." << endl;
                cout << "Resources: 1. Ore, 2. Wheat, 3. Sheep, 4. Wood, 5. Brick" << endl;
                size_t resource, amount, totalAmount = players[i]->numOfResources() / 2;
                while (totalAmount > 0){
                    cin >> resource >> amount;
                    if (resource < 1 || resource > 5 || amount < 0 || amount > players[i]->getResourceAmount(ResourceType(resource))){
                        cout << "Invalid input, try again" << endl;
                        continue;
                    }
                    if (amount > totalAmount){
                        cout << "You can't return more than half of your resources, try again" << endl;
                        continue;
                    }
                    totalAmount -= amount;
                    // good input
                    players[i]->removeResource(ResourceType(resource), amount);
                    cout << "You returned " << amount << " " << getResourceName(ResourceType(resource)) << " to the bank" << endl;
                    cout << "You still need to return " << totalAmount << " resources" << endl;
                    cout << *players[i] << endl;
                }
            }
        }
        if (count == 0){
            cout << "No player has more than 7 resources" << endl;
        }
    }

    int Catan::printWinner(){
        // find the player with the most victory points
        Player& mostVictoryPoints = *players[0];
        for (size_t i = 1; i < players.size(); i++){
            if (players[i]->getVictoryPoints() > mostVictoryPoints.getVictoryPoints()){
                mostVictoryPoints = *players[i];
            }
        }
        // check if the player with most points has 10 victory points
        if (mostVictoryPoints.getVictoryPoints() >= 10){
            cout << "The winner is: " << mostVictoryPoints.getName() << endl;
            return 1;       // someone won
        }
        return 0;       // no one won yet
    }

    Player& Catan::getPlayerById(int id){
        return *players[(size_t)id];
    }
}