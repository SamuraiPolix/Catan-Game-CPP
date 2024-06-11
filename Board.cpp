#include "Board.hpp"
#include "ResourceTypes.hpp"
#include <algorithm>
#include <random>
#include <ctime>
#include "Buildable.hpp"
#include <iostream>

using std::vector, string, cout, endl, shuffle, default_random_engine, begin, end;

namespace ariel {
    Board::Board(){
        // generate random board - set tiles with resources and numbers
        // first row has 3 tiles, second row has 4 tiles, third row has 5 tiles, fourth row has 4 tiles, fifth row has 3 tiles

        // All available tile lands
        // Resource: https://catan.fandom.com/wiki/Catan
        int allLands[19] = 
        {
            ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WOOD,     // 4 woods
            ResourceTypes::SHEEP, ResourceTypes::SHEEP, ResourceTypes::SHEEP, ResourceTypes::SHEEP,     // 4 sheeps
            ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WHEAT,     // 4 wheats
            ResourceTypes::BRICK, ResourceTypes::BRICK, ResourceTypes::BRICK,       // 3 bricks
            ResourceTypes::ORE, ResourceTypes::ORE, ResourceTypes::ORE,         // 3 ores
            ResourceTypes::DESERT
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
        for (int row = 0; i < 5; row++){
            // create each row (3, 4, 5, 4, 3 tiles)
            vector<Tile> tilesRow;
            int rowSize = 3;
            if (i == 1 || i == 3){
                rowSize = 4;
            } else if (i == 2){
                rowSize = 5;
            }
            for (int col = 0; col < rowSize; col++){
                // uses a number only if the land is not a desert
                if (allLands[landIndex] == ResourceTypes::DESERT){
                    tilesRow.push_back(Tile(allLands[landIndex], 0));
                } else {
                    tilesRow.push_back(Tile(allLands[landIndex], allNumbers[numberIndex]));
                    numberIndex++;
                }
                landIndex++;
            }
            this->board.push_back(tilesRow);
        }
    }
    
    int Board::placeSettlement(Player& owner, size_t tileX, size_t tileY, VertexPosition  tilePos){
        // check if the tile is empty 
        int status = this->board[tileX][tileY].setSettlementAt(tilePos, owner);
        if (status == 0){
            
        }
    }
    // void printBoard();
}