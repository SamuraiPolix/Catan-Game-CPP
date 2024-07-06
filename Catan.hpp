#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include <vector>
#include <iostream>

using std::vector;

namespace ariel {
    class Player;
    class Board;
    class DevelopmentCard;
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
        vector<Player*> getPlayers();
        Player& getCurrentPlayer();
        void ChooseStartingPlayer();
        Board* getBoard();
        void rolledSeven();
        void printBoard();
        void printPlayers();
        int printWinner();
        void nextPlayer();
        void printPlayersExceptCurrent();
        size_t addDevelopmentCard(Player& player);
        void giveResources(int diceRoll);
        Player& getPlayerById(int id);
    };
}