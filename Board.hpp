#pragma once
#include <vector>
#include <string>
#include "Tile.hpp"
#include "Buildable.hpp"

using std::vector, std::string;

#define NUM_OF_TILES 19

namespace ariel {
    class Tile;
    class Buildable;

    class Board
    {
    // private members
        vector<vector<Tile>> board;
        Buildable* buildables;
        Buildable* buildablesVertices;
        Buildable* buildablesEdges;

        // The whole board, seperated into the vertices in each tile
        // Used to have control over the Buildables from Board
        int boardVertices[NUM_OF_TILES][NUM_OF_VERTICES] = 
        {
            {0, 1, 2, 10, 9, 5},
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

    // private methods - mostly used to simplify API
        int hasBuildingNear(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos);
        int hasRoadNear(Player& owner, size_t tileX, size_t tileY, VertexPosition tilePos);
        int indexToTilePos(size_t index, size_t& tileX, size_t& tileY, VertexPosition& tilePos);
        int placeSettlement(Player& owner, size_t tileX, size_t tileY, VertexPosition  tilePos);
        int placeRoad(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos);
        int rowColPosToIndex(size_t row, size_t col, size_t pos);
        int indexToRowColPos(size_t index, size_t& row, size_t& col, size_t& pos);
    public:
        Board();
        ~Board();
        int placeSettlement(Player& owner, size_t index);
        int placeRoad(Player& owner, size_t index1, size_t index2);

        void getEdgeBetweenVertices(size_t& tileX1, size_t& tileY1, EdgePosition& tilePos1, size_t tileX2, size_t tileY2, EdgePosition tilePos2);

        void printBoard();
    };
}