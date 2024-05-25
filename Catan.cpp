#include "Catan.hpp"

namespace ariel {
    Catan::Catan(Player p1, Player p2, Player p3){
        this->players.push_back(p1);
        this->players.push_back(p2);
        this->players.push_back(p3);
        this->players.shrink_to_fit();
    }

    // void Catan::ChooseStartingPlayer();
    // Board& Catan::getBoard();
    // void Catan::printWinner();
}