#include "Board.hpp"
#include "Player.hpp"

using std::vector;

namespace ariel {
    class Catan
    {
    // private members
        vector<Player> players;
        size_t currPlayer;     // index of player in players, with current turn
        Board board;

    public:
        Catan(Player p1, Player p2, Player p3);
        Player& getCurrentPlayer() const;
        void ChooseStartingPlayer();
        Board& getBoard() const;
        void printWinner();
        int placeSettlement(Player& owner, size_t index);
        int placeRoad(Player& owner, size_t index);
        void nextPlayer();
        void printPlayersExceptCurrent();
    };
}