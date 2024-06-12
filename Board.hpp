#include <vector>
#include <string>
#include "Tile.hpp"

using std::vector, std::string;

namespace ariel {
    class Board
    {
    // private members
        vector<vector<Tile>> board;

    // private methods - mostly used to simplify API
        int hasBuildingNear(Player& owner, size_t tileX, size_t tileY, VertexPosition tilePos) const;
        int hasRoadNear(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos) const;
        int indexToTilePos(size_t& tileX, size_t& tileY, VertexPosition& tilePos) const;
        int placeSettlement(Player& owner, size_t tileX, size_t tileY, VertexPosition  tilePos);
        int placeRoad(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos);
    public:
        Board();
        int placeSettlement(Player& owner, size_t index);
        int placeRoad(Player& owner, size_t index);
        
        void printBoard();
    };
}