/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

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
    Board::Board() : buildablesVertices(54), buildablesEdges(72){
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
            ResourceType::Ore, ResourceType::Ore, ResourceType::Ore,         // 3 Ores
            ResourceType::Desert
        };

        //     1x"2"    2x"3"    2x"4"    2x"5"    2x"6"    2x"8"    2x"9"    2x"10"    2x"11"    1x"12"
        // Resource: https://catan.fandom.com/wiki/Catan
        int allNumbers[18] = 
        {
            2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12
        };

        // buildablesVertices = new Buildable[54];
        // buildablesEdges = new Buildable[72];
        
        // shuffle the lands and numbers by seed (to allow testing)
        shuffle(begin(allLands), end(allLands), default_random_engine(0));
        shuffle(begin(allNumbers), end(allNumbers), default_random_engine(0));

        #ifdef DEBUG
        // print board edges
        for (int i = 0; i < 19; i++){
            for (int j = 0; j < 6; j++){
                cout << "Tile " << i << " index " << j << " " << boardEdges[i][j] << endl;
            }
        }
        #endif

        
        // Init all Buildables vertices
        for (size_t i = 0; i < 54; i++){
            buildablesVertices[i] = BuildableVertex(i);
        }
        

        // Init all Buildables edges
        for (size_t i = 0; i < 72; i++){
            buildablesEdges[i] = BuildableEdge(i);
            #ifdef DEBUG
            cout << "edge" << i << " " << &buildablesEdges[i] << endl;
            #endif
        }

        #ifdef DEBUG
        // print board edges
        for (size_t i = 0; i < 19; i++){
            for (size_t j = 0; j < 6; j++){
                cout << "Tile " << i << " index " << j << " " << boardEdges[i][j] << endl;
            }
        }
        #endif

        // init board tiles with generated resources and numbers
        int landIndex = 0;
        int numberIndex = 0;
        int tile = 0;
        for (size_t row = 0; row < 5; row++){
            // create each row (3, 4, 5, 4, 3 tiles)
            size_t rowSize = 3;
            if (row == 1 || row == 3){
                rowSize = 4;
            } else if (row == 2){
                rowSize = 5;
            }
            vector<Tile*> tilesRow;
            for (size_t col = 0; col < rowSize; col++){
                // uses a number only if the land is not a desert
                if (allLands[landIndex] == ResourceType::Desert){
                    tilesRow.push_back(new Tile(row, col, (ResourceType)allLands[landIndex], (size_t)0));
                } else {
                    tilesRow.push_back(new Tile(row, col, (ResourceType)allLands[landIndex], (size_t)allNumbers[numberIndex]));
                    numberIndex++;
                }
                landIndex++;
                // set all positions to buildables created before
                for (size_t pos = 0; pos < NUM_OF_VERTICES; pos++){
                    tilesRow[tilesRow.size()-1]->setVertexAtPos(pos, &buildablesVertices[boardVertices[tile][pos]]);
                    tilesRow[tilesRow.size()-1]->setEdgeAtPos(pos, &buildablesEdges[boardEdges[tile][pos]]);

                    #ifdef DEBUG
                    cout << "row" << row << "col" << col << "pos" << pos  << " Tile " << tile << " index " << boardEdges[tile][pos] << " " << tilesRow[tilesRow.size()-1]->getEdge((EdgePosition)pos) << " - " << &buildablesEdges[boardEdges[tile][pos]] << endl;
                    #endif
                }
                tile++;
            }
            tilesRow.shrink_to_fit();
            this->board.push_back(tilesRow);
        }
        #ifdef DEBUG
        // print tiles addresses
        for (size_t i = 0; i < 5; i++){
            int rowsize = 3;
            if (i == 1 || i == 3){
                rowsize = 4;
            } else if (i == 2){
                rowsize = 5;
            }
            for (size_t j = 0; j < rowsize; j++){
                cout << "Tile " << i << " " << j << " " << &board[i][j] << endl;
            }
        }
        #endif
    }
    Board::~Board(){
        // for (size_t i = 0; i < 5; i++){
        //     for (size_t j = 0; j < board[i].size(); j++){
        //         delete board[i][j];
        //     }
        // }
        // for (size_t i = 0; i < 54; i++){
        //     delete &buildablesVertices[i];
        // }
        // for (size_t i = 0; i < 72; i++){
        //     delete &buildablesEdges[i];
        // }
    }

    int Board::placeSettlement(Player& owner, size_t index){
        size_t tileX, tileY, tilePos;
        if (indexToRowColPos(index, tileX, tileY, tilePos) == -1){
            throw std::invalid_argument("Failed to place settlement at " + std::to_string(index)
            + "\nInvalid index\n");
        }

        // If there is a settlement 2 vertices or 1 away from chosen vertex, can't place settlement there
        // iterate over all tiles, if tile has the vertex index, check 2 to the left and 2 to the right and 1 to the left and right of the vertex
        for (size_t row = 0; row < board.size(); row++){
            for (size_t col = 0; col < board[row].size(); col++){
                if (board[row][col]->hasIndexVertex(index)){
                    for (size_t pos = 0; pos < 6; pos++){
                        if (board[row][col]->getVertex((VertexPosition)pos)->getIndex() == index){
                            if (board[row][col]->getVertex((VertexPosition)pos-1)->getType() != BuildableTypes::None ||
                                board[row][col]->getVertex((VertexPosition)pos+1)->getType() != BuildableTypes::None)
                            {
                                throw std::invalid_argument("Failed to place settlement at " + std::to_string(tileY) + ", " + std::to_string(tileX) + " on " + std::to_string(tilePos)
                                + "\nThere is a building 1 vertex away from this vertex\n");
                            }
                            if (board[row][col]->getVertex((VertexPosition)pos-2)->getType() != BuildableTypes::None ||
                                board[row][col]->getVertex((VertexPosition)pos+2)->getType() != BuildableTypes::None)
                            {
                                throw std::invalid_argument("Failed to place settlement at " + std::to_string(tileY) + ", " + std::to_string(tileX) + " on " + std::to_string(tilePos)
                                + "\nThere is a building 2 vertices away from this vertex\n");
                            }
                        }
                    }
                }
            }
        }

        // If player doesn't already have 2 settlments - they can place them anywhere (if the vertex is free)
        if (owner.numOfSettlements() < 2){
            // try to place a settlement at the given position, returns 0 if successful, -1 if not
            if (this->board[tileY][tileX]->setSettlementAt((VertexPosition)tilePos, owner) == -1){
                throw std::invalid_argument("Failed to place settlement at " + std::to_string(tileY) + ", " + std::to_string(tileX) + " on " + std::to_string(tilePos)
                + "\nVertex is already taken\n");
            }

            // If this is the second settlement - these are the starting resources for the player
            if (owner.numOfSettlements() == 1){
                giveStartingResources(owner, index);
            }

            addTileToPlayer(owner, index);
            
            return 0;       // success
        }
        // else, player has 2 settlements and can only place them near their roads
        // We first need to make sure the player has a road near this vertex
        // Resource: https://www.catan.com/understand-catan/game-rules (page 4 bottom, 5 top)
        if (hasRoadNear(owner, tileX, tileY, (VertexPosition)tilePos) == -1){
            throw std::invalid_argument("Failed to place settlement at " + std::to_string(tileY) + ", " + std::to_string(tileX) + " on " + std::to_string(tilePos)
            + "\nPlayer " + owner.getName() + " does not have a road connecting to this vertex\n");
        }
        // Player has a road connecting to desired settlement

        // try to place a settlement at the given position, returns 0 if successful, -1 if not
        if (this->board[tileY][tileX]->setSettlementAt((VertexPosition)tilePos, owner) == -1){
            throw std::invalid_argument("Failed to place settlement at " + std::to_string(tileY) + ", " + std::to_string(tileX) + " on " + std::to_string(tilePos)
            + "\nVertex is already taken\n");
        }

        // this->board[tileY][tileX]->setSettlementAt(tilePos, owner);
        return 0;       // success
    }

    void Board::giveStartingResources(Player& owner, size_t vertexIndex){
        for (size_t row = 0; row < board.size(); row++){
            for (size_t col = 0; col < board[row].size(); col++){
                if (board[row][col]->hasIndexVertex(vertexIndex)){
                    owner.addResource(board[row][col]->getResource(), (size_t)1);
                }
            }
        }
    }

    int Board::placeRoad(Player& owner, size_t index1, size_t index2){
        size_t tileX, tileY, tilePos;
        if (indexToRowColPosRoad(index1, index2, tileX, tileY, tilePos) == -1){
            throw std::invalid_argument("Failed to place road  at " + std::to_string(index1) + ", " + std::to_string(index2)
            + "\nInvalid index\n");
        }

        // We first need to make sure the player has a settlement, city or road near this edge
        if (hasBuildingNear(owner, tileX, tileY, (EdgePosition)tilePos) == 0){
            throw std::invalid_argument("Failed to place road at Y,X " + std::to_string(tileY) + ", " + std::to_string(tileX) + " on " + std::to_string(tilePos)
            + "\nPlayer " + owner.getName() + " does not have a building near this edge\n");
        }
        // try to place a road at the given position, returns 0 if successful, -1 if not
        if (this->board[tileY][tileX]->setRoadAt((EdgePosition)tilePos, owner) == -1){
            throw std::invalid_argument("Failed to place road at Y,X " + std::to_string(tileY) + ", " + std::to_string(tileX) + " on " + std::to_string(tilePos)
            + "\nEdge is already taken\n");
        }
        // this->board[tileY][tileX]->setRoadAt(tilePos, owner);
        return 0;       // success
    }

    void Board::addTileToPlayer(Player& owner, size_t vertexIndex) {
        // iterate over all tiles, if tile has the vertex index, add it to the player's tiles
        for (size_t i = 0; i < this->board.size(); i++){
            for (size_t j = 0; j < this->board[i].size(); j++){
                if (this->board[i][j]->hasIndexVertex(vertexIndex)){
                    #ifdef DEBUG
                    cout << &this->board[i][j] << endl;
                    #endif
                    owner.addTile(this->board[i][j]);
                }
            }
        }
    }

    int Board::hasBuildingNear(Player& owner, size_t tileX, size_t tileY, EdgePosition tilePos){
        // check for a road to connect to around given pos
        if (hasRoadNear(owner, tileX, tileY, (VertexPosition)tilePos) == 1 || hasRoadNear(owner, tileX, tileY, (VertexPosition)tilePos+1) == 1){
            return 1;       // road near
        }
        // check if there is a building near on selected tile (check to the left and right of the vertex) - road was already checked
        if (this->board[tileY][tileX]->isVertexOwner((VertexPosition)tilePos, owner) ||
            this->board[tileY][tileX]->isVertexOwner((VertexPosition)tilePos+1, owner))
        {
            return 1;       
        }
        return 0;
    }

    int Board::hasRoadNear(Player& owner, size_t tileX, size_t tileY, VertexPosition tilePos){
        // check if there is a road near on selected tile (check to the left and right of the vertex)
        VertexPosition vp = (tilePos-1);
        EdgePosition ep = (EdgePosition)vp;
        if (this->board[tileY][tileX]->isEdgeOwner((EdgePosition)(tilePos-1), owner) ||
            this->board[tileY][tileX]->isEdgeOwner((EdgePosition)tilePos, owner))
        {
            return 1;       
        }
        // if not found on current tile, check the neighbor according to selected tilePos
        switch (tilePos){
            case VertexPosition::VERTEX_TOP_LEFT:
                if (tileX > 0 && this->board[tileY][tileX-1]->isEdgeOwner(EdgePosition::EDGE_TOP_RIGHT, owner) ||
                    tileY > 0 && tileX > 0 && this->board[tileY-1][tileX-1]->isEdgeOwner(EdgePosition::EDGE_BOTTOM_LEFT, owner))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_TOP:
                if ((tileY > 0 && tileX > 0 && this->board[tileY-1][tileX-1]->isEdgeOwner(EdgePosition::EDGE_RIGHT, owner)) ||
                    (tileY > 0 && tileX < this->board[tileY-1].size() && this->board[tileY-1][tileX]->isEdgeOwner(EdgePosition::EDGE_LEFT, owner)))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_TOP_RIGHT:
                if ((tileX < this->board[tileY].size()-1 && this->board[tileY][tileX+1]->isEdgeOwner(EdgePosition::EDGE_TOP_LEFT, owner) ||
                    (tileY > 0 && tileX < this->board[tileY-1].size()-1 && this->board[tileY-1][tileX]->isEdgeOwner(EdgePosition::EDGE_BOTTOM_RIGHT, owner))))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_BOTTOM_RIGHT:
                if ((tileX < this->board[tileY].size()-1 && this->board[tileY][tileX+1]->isEdgeOwner(EdgePosition::EDGE_BOTTOM_LEFT, owner) ||
                    (tileY < this->board.size()-1 && tileX < this->board[tileY-1].size() && this->board[tileY+1][tileX]->isEdgeOwner(EdgePosition::EDGE_TOP_RIGHT, owner))))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_BOTTOM:
                if ((tileY < this->board.size()-1 && tileX < this->board[tileY+1].size() && this->board[tileY+1][tileX]->isEdgeOwner(EdgePosition::EDGE_LEFT, owner) ||
                    (tileY < this->board.size()-1 && tileX > 0 && this->board[tileY+1][tileX-1]->isEdgeOwner(EdgePosition::EDGE_RIGHT, owner))))
                {
                    return 1;
                }
                break;
            case VertexPosition::VERTEX_BOTTOM_LEFT:
                if ((tileX > 0 && this->board[tileY][tileX-1]->isEdgeOwner(EdgePosition::EDGE_BOTTOM_RIGHT, owner) ||
                    (tileY < this->board.size()-1 && tileX > 0 && this->board[tileY+1][tileX-1]->isEdgeOwner(EdgePosition::EDGE_TOP_LEFT, owner))))
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

    int Board::rowColPosToIndex(size_t row, size_t col, size_t pos){
        int vertices = 0;
        int row_size;
        for (int i = 0; i <= row; i++){
            row_size = 3;
            if (i == 1 || i == 3){
                row_size = 4;
            } else if (i == 2){
                row_size = 5;
            }
            for (int j = 0; j < row_size; j++){
                if (row == i && col == j){
                    break;
                }
                vertices++;
            }
        }
        return boardVertices[vertices][pos];
    }

    int Board::indexToRowColPos(size_t index, size_t& col, size_t& row, size_t& pos){
        size_t rows = 0, cols = 0;
        for (size_t tile = 0; tile < 19; tile++){
            if (tile == 3 || tile == 7 || tile == 12 || tile == 16){
                rows++;
                cols = 0;
            }
            for (size_t j = 0; j < 6; j++){
                if (boardVertices[tile][j] == index){
                    row = rows;
                    col = cols;
                    pos = j;
                    #ifdef DEBUG
                    cout << "row: " << row << " col: " << col << " pos: " << pos << endl;
                    #endif
                    return 0;
                }
            }
            cols++;
        }
        return -1;
    }

    int Board::indexToRowColPosRoad(size_t index1, size_t index2, size_t& col, size_t& row, size_t& pos){
        size_t rows = 0, cols = 0;
        for (size_t tile = 0; tile < 19; tile++){
            if (tile == 3 || tile == 7 || tile == 12 || tile == 16){
                rows++;
                cols = 0;
            }
            for (size_t j = 0; j < 6; j++){
                if (boardVertices[tile][j] == index1 && j+1 < 6 && boardVertices[tile][j+1] == index2){
                    row = rows;
                    col = cols;
                    pos = j;
                    #ifdef DEBUG
                    cout << "row: " << row << " col: " << col << " pos: " << pos << endl;
                    #endif
                    return 0;
                }
                else if (boardVertices[tile][j] == index2 && j+1 < 6 && boardVertices[tile][j+1] == index1){
                    row = rows;
                    col = cols;
                    pos = j;
                    #ifdef DEBUG
                    cout << "row: " << row << " col: " << col << " pos: " << pos << endl;
                    #endif
                    return 0;
                }
            }
            cols++;
        }
        return -1;
    }
    
    void Board::printBoard(){
    size_t boardSize[] = {3, 4, 5, 4, 3};
    size_t padding[5] = {0, 5, 10, 5, 0};
    size_t numberOfRows = sizeof(boardSize) / sizeof(boardSize[0]);
    
    for (size_t row = 0; row < numberOfRows; ++row) {
        // Print the top vertices
        if (row == 0){
            std::cout << std::setw(35 - padding[row]) << " "; // Adjust leading spaces
            for (size_t col = 0; col < boardSize[row]; ++col) {
                cout << *board[row][col]->getVertex(VertexPosition::VERTEX_TOP);
                if (col < boardSize[row]) {
                    std::cout << std::setw(12);
                }
            }
            std::cout << std::endl;
        }

        // Print the top slashes and spaces between hexagons
        if (row < 3) {
            std::cout << std::setw(33 - padding[row]) << " "; // Adjust leading spaces
            for (size_t col = 0; col < boardSize[row]; ++col) {
                // if there is a road on this, color it with players color
                cout << *board[row][col]->getEdge(EdgePosition::EDGE_TOP_LEFT);
                cout << std::setw(5) << *board[row][col]->getEdge(EdgePosition::EDGE_TOP_RIGHT);
                if (col < boardSize[row]) {
                    std::cout << std::setw(7);
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout << std::setw(28 - padding[row]) << " "; // Adjust leading spaces
            for (size_t col = 0; col < boardSize[row]; ++col) {
                cout << *board[row-1][col]->getEdge(EdgePosition::EDGE_BOTTOM_LEFT);
                cout << std::setw(5) << *board[row-1][col]->getEdge(EdgePosition::EDGE_BOTTOM_RIGHT);
                if (col < boardSize[row]) {
                    std::cout << std::setw(7);
                }
            }
            std::cout << *board[row-1][boardSize[row-1]-1]->getEdge(EdgePosition::EDGE_BOTTOM_LEFT)
                        << std::setw(5) << *board[row-1][boardSize[row-1]-1]->getEdge(EdgePosition::EDGE_BOTTOM_RIGHT);
            std::cout << std::endl;
        }
        

        // Print the middle vertices
        std::cout << std::setw(30 - padding[row]) << " "; // Adjust leading spaces
        for (size_t col = 0; col < boardSize[row]; ++col) {
            cout << *board[row][col]->getVertex(VertexPosition::VERTEX_TOP_LEFT);
            if (col < boardSize[row]) {
                std::cout << std::setw(10) << " ";
            }
        }
        std::cout << *board[row][boardSize[row]-1]->getVertex(VertexPosition::VERTEX_TOP_RIGHT);
        std::cout << std::endl;

        // Print the vertical bars
        std::cout << std::setw(30 - padding[row]) << " "; // Adjust leading spaces
        for (size_t col = 0; col < boardSize[row]; ++col) {
            cout << *board[row][col]->getEdge(EdgePosition::EDGE_LEFT);
            std::cout << std::setw(2) << " " << getResourceName(board[row][col]->getResource()) << "(" << board[row][col]->getNumber() << ")";
            if (col < boardSize[row]) {
                std::cout << std::setw(2) << " ";
            }
        }
        std::cout << *board[row][boardSize[row]-1]->getEdge(EdgePosition::EDGE_RIGHT) << std::endl;

        // Print the bottom vertices
        std::cout << std::setw(30 - padding[row]) << " "; // Adjust leading spaces
        for (size_t col = 0; col < boardSize[row]; ++col) {
            cout << *board[row][col]->getVertex(VertexPosition::VERTEX_BOTTOM_LEFT);
            if (col < boardSize[row]) {
                std::cout << std::setw(12);
            }
        }
        // std::cout << row << (boardSize[row] - 1) << VERTEX_BOTTOM_RIGHT;
        std::cout << *board[row][boardSize[row]-1]->getVertex(VertexPosition::VERTEX_BOTTOM_RIGHT);
        std::cout << std::endl;

        // Print the bottom slashes and spaces between hexagons
        if (row == 4){
            std::cout << std::setw(34 -  padding[row]) << " "; // Adjust leading spaces
            for (size_t col = 0; col < boardSize[row]; ++col) {
                std::cout << *board[row][col]->getEdge(EdgePosition::EDGE_BOTTOM_LEFT);
                cout << std::setw(5) << *board[row][col]->getEdge(EdgePosition::EDGE_BOTTOM_RIGHT);
                if (col < boardSize[row]) {
                    std::cout << std::setw(7);
                }
            }
            std::cout << std::endl;
        }

    }

    // print bottom vertice bottom row
    std::cout << std::setw(38 - padding[4]); // Adjust leading spaces
    for (size_t col = 0; col < boardSize[4]; ++col) {
        // std::cout << numberOfRows-1 << col << VERTEX_BOTTOM;
        cout << *board[numberOfRows-1][col]->getVertex(VertexPosition::VERTEX_BOTTOM);
        if (col < boardSize[4]-1) {
            std::cout << std::setw(12);
        }
    }
    std::cout << std::endl;
    }
}