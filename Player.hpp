/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

#pragma once
#include "Board.hpp"
#include "Catan.hpp"
#include <string>
#include <vector>
#include <map>
#include "Types.hpp"
#include "DevelopmentCard.hpp"
#include "Tile.hpp"
#include <tuple>

using std::vector, std::string, std::map, std::tuple, std::ostream;

namespace ariel{
    class Board;
    class Catan;
    class Buildable;
    class Tile;
    class Player
    {
        static int playerCounter;
        static Color colors[3];

        private:        // by default
            string name;
            size_t resources[5];       // holds the amount of each resource (index i := ResourceType(i+1))
            vector<tuple<size_t, size_t>> roads;
            vector<size_t> settlements;     // holds board index of all settlements
            vector<Tile> tiles;     // holds the tiles that the player has settlements on
            bool currTurn;
            vector<DevelopmentCard*> developmentCards;
            int victoryPoints;
            int knights;
            Color color;
            bool hasLargestArmy;
            // Catan catan;

        public:
            Player(string name);
            int placeSettlement(size_t index, Board* board);
            int placeRoad(size_t vertex1, size_t vertex2, Board* board);
            size_t printDevelopmentCards();
            size_t buyDevelopmentCard(Catan& catan);
            size_t addDevelopmentCard(DevelopmentCard& card);
            size_t numOfResources();
            int useDevelopmentCard(size_t indexInHand);
            void printPoints();
            void trade(Player& player, ResourceType resourceSent, ResourceType resourceReceived, const size_t& amountSent, const size_t& amountReceived);
            void trade(Player& player, vector<tuple<ResourceType, size_t>>& resourcesSent, vector<tuple<ResourceType, size_t>>& resourcesReceived);
            void rollDice(Catan& catan);
            void endTurn(Catan& catan);
            void startTurn();
            bool availableResourcesDevelopmentCard();
            bool availableResourcesBuildable(BuildableTypes type);
            string getName() const;
            int numOfSettlements();
            int numOfRoads();
            size_t getResourceAmount(ResourceType resource);
            void addTile(Tile& tile);
            void addResource(ResourceType resource, size_t amount);
            void removeResource(ResourceType resource, size_t amount);
            int getVictoryPoints();
            int addVictoryPoints(size_t points);
            void updateLargestArmy();
            // int addTilesByIndex(size_t index);
            vector<Tile>& getTiles();
            Color getColor();
            friend ostream& operator<<(ostream& os, const Player& player);
    };
}