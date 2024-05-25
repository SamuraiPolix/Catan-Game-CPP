#include "Board.hpp"
#include "Player.hpp"

using std::vector;

namespace ariel {
    class Catan
    {
    // private by default
        vector<Player> players;
        Player currentPlayer;
        Board board;

    public:
        Catan(Player p1, Player p2, Player p3);
        void ChooseStartingPlayer();
        Board& getBoard();
        void printWinner();
    };
}