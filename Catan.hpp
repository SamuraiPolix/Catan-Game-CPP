#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "DevelopmentCard.hpp"
#include <vector>
#include <iostream>

using std::vector;

namespace ariel {
    class Player;
    class Board;
    class Catan
    {
    // private members
        vector<Player*> players;
        int currPlayer;     // index of player in players, with current turn
        Board *board;
        vector<DevelopmentCard*> developmentCards;

    // private methods
        void initCards();

    public:
        Catan(Player& p1, Player& p2, Player& p3);
        ~Catan();
        Player& getCurrentPlayer();
        void ChooseStartingPlayer();
        Board* getBoard();
        int printWinner();
        void nextPlayer();
        void printPlayersExceptCurrent();
        void addDevelopmentCard(Player& player);
        void giveResources(int diceRoll);
        Player& getPlayerById(int id);
    };
}