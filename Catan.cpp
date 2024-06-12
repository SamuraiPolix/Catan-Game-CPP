#include "Catan.hpp"
#include <random>
#include <ctime>
#include <iostream>

using std::cout, std::endl, std::rand;
namespace ariel {
    Catan::Catan(Player p1, Player p2, Player p3){
        this->players.push_back(p1);
        this->players.push_back(p2);
        this->players.push_back(p3);
        this->players.shrink_to_fit();
    }

    // this functions generates a random player and prints its name
    void Catan::ChooseStartingPlayer(){
        srand(time(0));
        this->currPlayer = rand() % 3;
        std::cout << "The starting player is: " << this->getCurrentPlayer().getName() << std::endl;
    }

    // returns the current playing player
    Player& Catan::getCurrentPlayer() const{
        return this->players[this->currPlayer];
    }

    Board& Catan::getBoard() const{
        return this->board;
    }
    void Catan::printWinner(){
        // to be implemented
    }
    int Catan::placeSettlement(Player& owner, size_t index){
        return board.placeSettlement(owner, index);
    }
    int Catan::placeRoad(Player& owner, size_t index){
        return board.placeRoad(owner, index);
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
}