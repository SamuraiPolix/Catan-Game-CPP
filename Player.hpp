#pragma once
#include "Board.hpp"
#include "Catan.hpp"
#include <string>
#include <vector>
#include <map>
#include "Types.hpp"
#include "Buildable.hpp"
#include "DevelopmentCard.hpp"
#include "Tile.hpp"
#include <tuple>

using std::vector, std::string, std::map, std::tuple;

namespace ariel{
    class Board;
    class Catan;
    class Player
    {
        static int playerCounter;
        static Color colors[3];

        private:        // by default
            string name;
            int resources[5];       // holds the amount of each resource (index i := ResourceType(i+1))
            vector<tuple<size_t, size_t>> roads;
            vector<size_t> settlements;     // holds board index of all settlements
            vector<Tile> tiles;     // holds the tiles that the player has settlements on
            bool currTurn;
            vector<DevelopmentCard*> developmentCards;
            int victoryPoints;
            Color color;
            // Catan catan;

        public:
            Player(string name);
            int placeSettlement(size_t index, Board* board);
            int placeRoad(size_t vertex1, size_t vertex2, Board* board);
            void buyDevelopmentCard(Catan& catan);
            void addDevelopmentCard(DevelopmentCard& card);
            void printPoints();
            void trade(Player& player, ResourceType resourceSent, ResourceType resourceReceived, const int& amountSent, const int& amountReceived);
            void rollDice(Catan& catan);
            void endTurn(Catan& catan);
            void startTurn();
            string getName();
            int numOfSettlements();
            int numOfRoads();
            int getResourceAmount(ResourceType resource);
            void addTile(Tile& tile);
            void addResource(ResourceType resource, int amount);
            int getVictoryPoints();
            int addVictoryPoints(size_t points);
            int addTilesByIndex(size_t index);
            vector<Tile>& getTiles();
            Color getColor();
    };
}