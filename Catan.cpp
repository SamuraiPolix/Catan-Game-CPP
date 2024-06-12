#include "Catan.hpp"
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "ResourceTypes.hpp"

using std::cout, std::endl, std::rand, std::srand, std::time, std::shuffle, std::default_random_engine, std::invalid_argument;
namespace ariel {
    Catan::Catan(Player p1, Player p2, Player p3) : board(){
        this->players.push_back(p1);
        this->players.push_back(p2);
        this->players.push_back(p3);
        this->players.shrink_to_fit();
        this->developmentCards = vector<DevelopmentCard*>(25, NULL);

        initCards();
    }

    // this functions generates a random player and prints its name
    void Catan::ChooseStartingPlayer(){
        srand(time(0));
        this->currPlayer = rand() % 3;
        std::cout << "The starting player is: " << this->getCurrentPlayer().getName() << std::endl;
    }

    // returns the current playing player
    Player& Catan::getCurrentPlayer(){
        return this->players[(size_t)this->currPlayer];
    }

    Board& Catan::getBoard(){
        return *this->board;
    }
    int Catan::placeSettlement(Player& owner, size_t index){
        return board->placeSettlement(owner, index);
    }
    int Catan::placeRoad(Player& owner, size_t index){
        return board->placeRoad(owner, index);
    }
    void Catan::nextPlayer(){
        this->currPlayer = (this->currPlayer + 1) % 3;
        getCurrentPlayer().startTurn();
    }
    void Catan::printPlayersExceptCurrent(){
        for (size_t i = 0; i < players.size(); i++){
            if (i != this->currPlayer){
                cout << i << ". " << this->players[i].getName() << endl;
            }
        }
    }

    void Catan::initCards(){
        // In the base game, there are 25 development cards: 14 knight cards, 5 victory point cards, 2 road building, 2 year of plenty, and 2 monopoly. 
        // Source: https://catan.fandom.com/wiki/Development_card
        for (int i = 0; i < 14; i++){
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::Knight));
        }
        for (int i = 0; i < 5; i++){
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::VictoryPoint));
        }
        for (int i = 0; i < 2; i++){
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::RoadBuilding));
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::YearOfPlenty));
            developmentCards.push_back(DevelopmentCardFactory::createCard(CardType::Monopoly));
        }

        developmentCards.shrink_to_fit();

        // shuffle the cards
        shuffle(developmentCards.begin(), developmentCards.end(), default_random_engine(0));
    }

    void Catan::addDevelopmentCard(Player& player){
        // add development card
        player.addDevelopmentCard(*developmentCards.back());
        // print the card
        cout << "Player " << player.getName() << " bought a development card" << endl;
        cout << "The card is: " << developmentCards.back() << endl;
        developmentCards.pop_back();
    }

    void Catan::giveResources(int diceRoll){
        for (size_t i = 0; i < players.size(); i++){
            for (size_t j = 0; j < players[i].numOfSettlements(); j++){
                if (players[i].getTiles()[j].getNumber() == diceRoll){
                    ResourceType resource = players[i].getTiles()[j].getResource();
                    players[i].addResource(resource, 1);
                }
            }
        }
    }

    int Catan::printWinner(){
        // iterate over all players, if someone has 10 points, he won
        for (size_t i = 0; i < players.size(); i++){
            if (players[i].getVictoryPoints() >= 10){
                cout << "The winner is: " << players[i].getName() << endl;
                return 1;       // someone won
            }
        }
        return 0;       // no one won yet
    }

    Player& Catan::getPlayerById(int id){
        return players[(size_t)id];
    }
}