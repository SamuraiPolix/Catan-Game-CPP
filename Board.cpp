#include "Board.hpp"
#include "Types.hpp"
#include <algorithm>
#include <random>
#include <ctime>
#include "Buildable.hpp"
#include <iostream>
#include <iomanip>

using std::vector, std::string, std::cout, std::endl, std::shuffle, std::default_random_engine, std::begin, std::end;

namespace ariel {
    Board::Board() : board(5, std::vector<Tile>(3)) {
        // generate random board - set tiles with resources and numbers
        // first row has 3 tiles, second row has 4 tiles, third row has 5 tiles, fourth row has 4 tiles, fifth row has 3 tiles

        // All available tile lands
        // Resource: https://catan.fandom.com/wiki/Catan
        int allLands[19] = 
        {
            ResourceType::Wood, ResourceType::Wood, ResourceType::Wood, ResourceType::Wood,     // 4 Woods
            ResourceType::Sheep, ResourceType::Sheep, ResourceType::Sheep, ResourceType::Sheep,     // 4 Sheeps
            ResourceType::Wheat, ResourceType::Wheat, ResourceType::Wheat, ResourceType::Wheat,     // 4 Wheats
            ResourceType::Brick, ResourceType::Brick, ResourceType::Brick,       // 3 Bricks
            ResourceType::Ore, ResourceType::Ore, ResourceType::Ore,         // 3 Ores            ResourceType::DESERT
        };

        //     1x"2"    2x"3"    2x"4"    2x"5"    2x"6"    2x"8"    2x"9"    2x"10"    2x"11"    1x"12"
        // Resource: https://catan.fandom.com/wiki/Catan
        int allNumbers[18] = 
        {
            2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12
        };
        
        // shuffle the lands and numbers by seed (to allow testing)
        shuffle(begin(allLands), end(allLands), default_random_engine(0));
        shuffle(begin(allNumbers), end(allNumbers), default_random_engine(0));

        // init board tiles with generated resources and numbers
        int landIndex = 0;
        int numberIndex = 0;
        for (int row = 0; row < 5; row++){
            // create each row (3, 4, 5, 4, 3 tiles)
            vector<Tile> tilesRow;
            int rowSize = 3;
            if (row == 1 || row == 3){
                rowSize = 4;
            } else if (row == 2){
                rowSize = 5;
            }
            for (int col = 0; col < rowSize; col++){
                // uses a number only if the land is not a desert
                if (allLands[landIndex] == ResourceType::Desert){
                    tilesRow.push_back(Tile((ResourceType)allLands[landIndex], (size_t)0));
                } else {
                    tilesRow.push_back(Tile((ResourceType)allLands[landIndex], (size_t)allNumbers[numberIndex]));
                    numberIndex++;
                }
                landIndex++;
            }
            tilesRow.shrink_to_fit();
            this->board.push_back(tilesRow);
        }
    }

    int Board::placeSettlement(Player& owner, size_t index){
        size_t tileX, tileY;
        VertexPosition tilePos;
        if (indexToTilePos(index, tileX, tileY, tilePos) == -1){
            cout << "Invalid index" << endl;
            return -1;
        }
        return placeSettlement(owner, tileX, tileY, tilePos);
    }

    int Board::placeRoad(Player& owner, size_t index){
        size_t tileX, tileY;
        EdgePosition tilePos;
        VertexPosition tilePos2;
        if (indexToTilePos(index, tileX, tileY, tilePos2) == -1){
            cout << "Invalid index" << endl;
            return -1;
        }
        tilePos = (EdgePosition)tilePos2;
        return placeRoad(owner, tileX, tileY, tilePos);
    }
    
    int Board::placeSettlement(Player& owner, size_t tileX, size_t tileY, VertexPosition  tilePos){
        // If player doesn't already have 2 settlments - they can place them anywhere (if the vertex is free)
        if (owner.numOfSettlements() < 2){
            // try to place a settlement at the given position, returns 0 if successful, -1 if not
            if (this->board[tileY][tileX].setSettlementAt(tilePos, owner) == -1){
                cout << "Failed to place settlement at " << (int)tileX << ", " << (int)tileY << " on " << (int)tilePos << endl;
                cout << "Vertex is already taken" << endl;
                return 0;
            }
            this->board[tileY][tileX].setSettlementAt(tilePos, owner);
            owner.addTile(this->board[tileY][tileX]);
            return 1;       // success
        }
        // else, player has 2 settlements and can only place them near their roads
        // We first need to make sure the player has a road near this vertex
        // Resource: https://www.catan.com/understand-catan/game-rules (page 4 bottom, 5 top)
        if (hasRoadNear(owner, tileX, tileY, tilePos) == -1){
            cout << "Failed to place settlement at " << (int)tileX << ", " << (int)tileY << " on " << (int)tilePos << endl;
            cout << "Player " << owner.getName() << " does not have a road connecting to this vertex" << endl;
            return 0;      // failed to place settlement
        }
        // Player has a road connecting to desired settlement
        // try to place a settlement at the given position, returns 0 if successful, -1 if not
        if (this->board[tileY][tileX].setSettlementAt(tilePos, owner) == -1){
            cout << "Failed to place settlement at " << (int)tileX << ", " << (int)tileY << " on " << (int)tilePos << endl;
            cout << "Vertex is already taken" << endl;
            return 0;
        }
        this->board[tileY][tileX].setSettlementAt(tilePos, owner);
        return 1;       // success
    }

    int Board::placeRoad(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos){
        // We first need to make sure the player has a settlement, city or road near this edge
        if (hasBuildingNear(owner, tileX, tileY, tilePos) == 0){
            cout << "Failed to place road at " << (int)tileX << ", " << (int)tileY << " on " << (int)tilePos << endl;
            return 0;
        }
        // try to place a road at the given position, returns 0 if successful, -1 if not
        if (this->board[tileY][tileX].setRoadAt(tilePos, owner) == -1){
            cout << "Failed to place road at " << (int)tileX << ", " << (int)tileY << " on " << (int)tilePos << endl;
            cout << "Edge is already taken" << endl;
            return 0;
        }
        this->board[tileY][tileX].setRoadAt(tilePos, owner);
        return 1;       // success
    }

    int Board::hasBuildingNear(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos){
        // check for a road to connect to around given pos
        if (hasRoadNear(owner, tileX, tileY, (VertexPosition)tilePos) == 1 || hasRoadNear(owner, tileX, tileY, (VertexPosition)tilePos+1) == 1){
            return 1;       // road near
        }
        // check if there is a building near on selected tile (check to the left and right of the vertex) - road was already checked
        if (this->board[tileY][tileX].getVertex((VertexPosition)tilePos).getOwner().getName() == owner.getName() ||
            this->board[tileY][tileX].getVertex((VertexPosition)tilePos+1).getOwner().getName() == owner.getName())
        {
            return 1;       
        }
        return 0;
    }

    int Board::hasRoadNear(Player& owner, size_t tileX, size_t tileY, VertexPosition tilePos){
        // check if there is a road near on selected tile (check to the left and right of the vertex)
        if (this->board[tileY][tileX].getEdge((EdgePosition)tilePos-1).getOwner().getName() == owner.getName() ||
            this->board[tileY][tileX].getEdge((EdgePosition)tilePos).getOwner().getName() == owner.getName())
        {
            return 1;       
        }
        // if not found on current tile, check the neighbor according to selected tilePos
        switch (tilePos){
            case VertexPosition::VERTEX_TOP_LEFT:
                if ((tileX > 0 && this->board[tileY][tileX-1].getEdge(EdgePosition::EDGE_TOP_RIGHT).getOwner().getName() == owner.getName()) ||
                    (tileY > 0 && tileX > 0 && this->board[tileY-1][tileX-1].getEdge(EdgePosition::EDGE_BOTTOM_LEFT).getOwner().getName() == owner.getName()))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_TOP:
                if ((tileY > 0 && tileX > 0 && this->board[tileY-1][tileX-1].getEdge(EdgePosition::EDGE_RIGHT).getOwner().getName() == owner.getName()) ||
                    (tileY > 0 && tileX < this->board[tileY-1].size() && this->board[tileY-1][tileX].getEdge(EdgePosition::EDGE_LEFT).getOwner().getName() == owner.getName()))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_TOP_RIGHT:
                if ((tileX < this->board[tileY].size() && this->board[tileY][tileX+1].getEdge(EdgePosition::EDGE_TOP_LEFT).getOwner().getName() == owner.getName()) ||
                    (tileY > 0 && tileX < this->board[tileY-1].size() && this->board[tileY-1][tileX].getEdge(EdgePosition::EDGE_BOTTOM_RIGHT).getOwner().getName() == owner.getName()))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_BOTTOM_RIGHT:
                if ((tileX < this->board[tileY].size()-1 && this->board[tileY][tileX+1].getEdge(EdgePosition::EDGE_BOTTOM_LEFT).getOwner().getName() == owner.getName()) ||
                    (tileY < this->board.size()-1 && tileX < this->board[tileY-1].size() && this->board[tileY+1][tileX].getEdge(EdgePosition::EDGE_TOP_RIGHT).getOwner().getName() == owner.getName()))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_BOTTOM:
                if ((tileY < this->board.size()-1 && tileX < this->board[tileY+1].size() && this->board[tileY+1][tileX].getEdge(EdgePosition::EDGE_LEFT).getOwner().getName() == owner.getName()) ||
                    (tileY < this->board.size()-1 && tileX > 0 && this->board[tileY+1][tileX-1].getEdge(EdgePosition::EDGE_RIGHT).getOwner().getName() == owner.getName()))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_BOTTOM_LEFT:
                if ((tileX > 0 && this->board[tileY][tileX-1].getEdge(EdgePosition::EDGE_BOTTOM_RIGHT).getOwner().getName() == owner.getName()) ||
                    (tileY < this->board.size()-1 && tileX > 0 && this->board[tileY+1][tileX-1].getEdge(EdgePosition::EDGE_TOP_LEFT).getOwner().getName() == owner.getName()))
                {
                    return 1;
                }
                break;
            default:
                cout << "Invalid vertex position" << endl;
                break;
        }
        return 0;       // no road near
    }
    
    
    int Board::indexToTilePos(size_t index, size_t& tileX, size_t& tileY, VertexPosition& tilePos) {
        tileY = (index / 100) % 10;
        tileX = (index / 10) % 10;
        int _tilePos = index % 10;
        tilePos = (VertexPosition)_tilePos;
        if (tileY >= 5 || tileY < 0 || tileX >= this->board[tileY].size() || tileX < 0 || _tilePos >= 6 || _tilePos < 0){
            return -1;     // invalid index
        }
        return 0;       // success
    }
    
    void Board::printBoard(){
        // size_t row = 0, col = 0;

        // std::cout << std::setw(30) << row << col++ << VertexPosition::VERTEX_TOP
        //               << std::setw(10) << row << col++ << VertexPosition::VERTEX_TOP
        //               << std::setw(10) << row << col++ << VertexPosition::VERTEX_TOP
        //               << std::endl;

        // std::cout << std::setw(29) << "/" << std::setw(5) << "\\" << std::setw(7) << "/" << std::setw(5) << "\\" << std::setw(7) << "/" << std::setw(5) << "\\" << std::endl;
        
        // col = 0;

        // std::cout << std::setw(24) << row << col++ << VertexPosition::VERTEX_TOP_LEFT 
        //             << std::setw(10) << row << col++ << VertexPosition::VERTEX_TOP_LEFT
        //             << std::setw(10) << row << col << VertexPosition::VERTEX_TOP_LEFT
        //             << std::setw(10) << row << col << VertexPosition::VERTEX_TOP_RIGHT
        //             << std::endl;

        // std::cout << std::setw(25) << "|" << std::setw(12) << "|" << std::setw(12) << "|" << std::setw(12) << "|" << std::endl;

        // col = 0;

        // std::cout << std::setw(24) << row << col++ << VertexPosition::VERTEX_BOTTOM_LEFT
        //             << std::setw(10) << row << col++ << VertexPosition::VERTEX_BOTTOM_LEFT
        //             << std::setw(10) << row << col << VertexPosition::VERTEX_BOTTOM_LEFT
        //             << std::setw(10) << row << col << VertexPosition::VERTEX_BOTTOM_RIGHT
        //             << std::endl;
                
        // std::cout << std::setw(23) << "/" << std::setw(5) << "\\" << std::setw(7) << "/" << std::setw(5) << "\\" << std::setw(7) << "/" << std::setw(5) << "\\" << std::setw(7) << "/" << std::setw(5) << "\\" << std::endl;

        // col = 0;
        // row++;

        size_t boardSize[] = {3, 4, 5, 4, 3};
        size_t padding[5] = {0, 5, 10, 5, 0};
    size_t numberOfRows = sizeof(boardSize) / sizeof(boardSize[0]);
    size_t vertexCounter = 0;
    
    for (size_t row = 0; row < numberOfRows; ++row) {
        // Print the top vertices
        if (row == 0){
                    std::cout << std::setw(30 - padding[row]); // Adjust leading spaces
        for (size_t col = 0; col < boardSize[row]; ++col) {
            std::cout << row << col << VERTEX_TOP;
            if (col < boardSize[row] - 1) {
                std::cout << std::setw(10);
            }
        }
        std::cout << std::endl;

        }

        // Print the top slashes and spaces between hexagons
        if (row < 3) {
            std::cout << std::setw(29 - padding[row]); // Adjust leading spaces
            for (size_t col = 0; col < boardSize[row]; ++col) {
                    std::cout << "/" << std::setw(5) << "\\" << std::setw(7);
            }
            std::cout << std::endl;
        }
        else {
            std::cout << std::setw(23 - padding[row]); // Adjust leading spaces
            for (size_t col = 0; col <= boardSize[row]; ++col) {
                    std::cout << "\\" << std::setw(5) << "/" << std::setw(7);
            }
            std::cout << std::endl;
        }
        

        // Print the middle vertices
        std::cout << std::setw(24 - padding[row]); // Adjust leading spaces
        for (size_t col = 0; col < boardSize[row]; ++col) {
            std::cout << row << col << VERTEX_TOP_LEFT;
            if (col < boardSize[row]) {
                std::cout << std::setw(10);
            }
        }
        std::cout << row << (boardSize[row] - 1) << VERTEX_TOP_RIGHT;
        std::cout << std::endl;

        // Print the vertical bars
        std::cout << std::setw(25 - padding[row]); // Adjust leading spaces
        for (size_t col = 0; col < boardSize[row]; ++col) {
            std::cout << "|" << std::setw(12);
        }
        std::cout << "|" << std::endl;

        // Print the bottom vertices
        std::cout << std::setw(24 - padding[row]); // Adjust leading spaces
        for (size_t col = 0; col < boardSize[row]; ++col) {
            std::cout << row << col << VERTEX_BOTTOM_LEFT;
            if (col < boardSize[row]) {
                std::cout << std::setw(10);
            }
        }
        std::cout << row << (boardSize[row] - 1) << VERTEX_BOTTOM_RIGHT;
        std::cout << std::endl;

        // Print the bottom slashes and spaces between hexagons
        if (row == 4){
            std::cout << std::setw(29 -  padding[row]); // Adjust leading spaces
            for (size_t col = 0; col < boardSize[row]; ++col) {
                std::cout << "\\" << std::setw(5) << "/" << std::setw(7);
            }
            std::cout << std::endl;
        }

        vertexCounter++;
    }

    // print bottom vertice bottom row
    std::cout << std::setw(30 - padding[4]); // Adjust leading spaces
    for (size_t col = 0; col < boardSize[4]; ++col) {
        std::cout << numberOfRows-1 << col << VERTEX_BOTTOM;
        if (col < boardSize[4] - 1) {
            std::cout << std::setw(10);
        }
    }
    std::cout << std::endl;
    }
}