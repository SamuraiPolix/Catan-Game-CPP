/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

#pragma once
#include <vector>
#include <string>
#include "Tile.hpp"
#include "Buildable.hpp"
#include "Player.hpp"

using std::vector, std::string;

#define NUM_OF_TILES 19

namespace ariel {

    class Board
    {
    // private members
        vector<vector<Tile*>> board;
        vector<BuildableVertex> buildablesVertices;
        vector<BuildableEdge> buildablesEdges;

        // The whole board, seperated into the vertices in each tile
        // Used to have control over the Buildables from Board
        size_t boardVertices[NUM_OF_TILES][NUM_OF_VERTICES] = 
        {
            {0, 1, 2, 10, 9, 8},
            {2, 3, 4, 12, 11, 10},
            {4, 5, 6, 14, 13, 12},
            {7, 8, 9, 19, 18, 17},
            {9, 10, 11, 21, 20, 19},
            {11, 12, 13, 23, 22, 21},
            {13, 14, 15, 25, 24, 23},
            {16, 17, 18, 29, 28, 27},
            {18, 19, 20, 31, 30, 29},
            {20, 21, 22, 33, 32, 31},
            {22, 23, 24, 35, 34, 33},
            {24, 25, 26, 37, 36, 35},
            {28, 29, 30, 40, 39, 38},
            {30, 31, 32, 42, 41, 40},
            {32, 33, 34, 44, 43, 42},
            {34, 35, 36, 46, 45, 44},
            {39, 40, 41, 49, 48, 47},
            {41, 42, 43, 51, 50, 49},
            {43, 44, 45, 53, 52, 51}
        };

        size_t boardEdges[NUM_OF_TILES][NUM_OF_VERTICES] =
        {
            {0, 1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10, 2},
            {11, 12, 13, 14, 15, 8},
            {16, 4, 17, 18, 19, 20},
            {3, 10, 21, 22, 23, 17},
            {9, 15, 24, 25, 26, 21},
            {14, 27, 28, 29, 30, 24},
            {31, 19, 32, 33, 34, 35},
            {18, 23, 36, 37, 38, 32},
            {22, 26, 39, 40, 41, 36},
            {25, 30, 42, 43, 44, 39},
            {29, 45, 46, 47, 48, 42},
            {33, 38, 49, 50, 51, 52},
            {37, 41, 53, 54, 55, 49},
            {40, 44, 56, 57, 58, 53},
            {43, 48, 59, 60, 61, 56},
            {50, 55, 62, 63, 64, 65},
            {54, 58, 66, 67, 68, 62},
            {57, 61, 69, 70, 71, 66}
        };

    // private methods - mostly used to simplify API
        int hasBuildingNear(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos);
        int hasRoadNear(Player& owner, size_t tileX, size_t tileY, VertexPosition tilePos);
        int indexToTilePos(size_t index, size_t& tileX, size_t& tileY, VertexPosition& tilePos);
        int placeSettlement(Player& owner, size_t tileX, size_t tileY, VertexPosition  tilePos);
        int placeRoad(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos);
        int rowColPosToIndex(size_t row, size_t col, size_t pos);
        int indexToRowColPos(size_t index, size_t& row, size_t& col, size_t& pos);
        int indexToRowColPosRoad(size_t index1, size_t index2, size_t& row, size_t& col, size_t& pos);
        void addTileToPlayer(Player& owner, size_t tileIndex);
        void giveStartingResources(Player& owner, size_t vertexIndex);
    public:
        Board();
        // ~Board() = default;
        ~Board();
        int placeSettlement(Player& owner, size_t index);
        int placeRoad(Player& owner, size_t index1, size_t index2);

        void getEdgeBetweenVertices(size_t& tileX1, size_t& tileY1, EdgePosition& tilePos1, size_t tileX2, size_t tileY2, EdgePosition tilePos2);

        void printBoard();
    };
}