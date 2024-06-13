#pragma once
#include <vector>
#include <string>
#include "Tile.hpp"
#include "Buildable.hpp"

using std::vector, std::string;

namespace ariel {
    class Tile;
    class Buildable;

    class Board
    {
    // private members
        vector<vector<Tile>> board;

    // private methods - mostly used to simplify API
        int hasBuildingNear(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos);
        int hasRoadNear(Player& owner, size_t tileX, size_t tileY, VertexPosition tilePos);
        int indexToTilePos(size_t index, size_t& tileX, size_t& tileY, VertexPosition& tilePos);
        int placeSettlement(Player& owner, size_t tileX, size_t tileY, VertexPosition  tilePos);
        int placeRoad(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos);
    public:
        Board();
        int placeSettlement(Player& owner, size_t index);
        int placeRoad(Player& owner, size_t index);
        
        void printBoard();
    };
}