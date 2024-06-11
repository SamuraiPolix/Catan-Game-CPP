#include "Board.hpp"
#include "Player.hpp"

using std::vector;

namespace ariel {
    class Catan
    {
    // private by default
        vector<Player> players;
        size_t currPlayer;     // index of player in players, with current turn
        Board board;

    public:
        Catan(Player p1, Player p2, Player p3);
        Player& getCurrentPlayer();
        void ChooseStartingPlayer();
        Board& getBoard();
        void printWinner();
    };
}