#include <vector>
#include <string>
#include "Tile.hpp"

using std::vector, std::string;

namespace ariel {
    class Board
    {
    private:
        vector<vector<Tile>> board;


    public:
        Board();
        
        int placeSettlement(Player& owner, size_t tileX, size_t tileY, VertexPosition  tilePos);
        int placeRoad(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos);
        void printBoard();
    };
}