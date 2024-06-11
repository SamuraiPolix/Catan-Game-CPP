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
    Player& Catan::getCurrentPlayer(){
        return this->players[this->currPlayer];
    }

    Board& Catan::getBoard(){
        return this->board;
    }
    void Catan::printWinner(){
        // to be implemented
    }
}