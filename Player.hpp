#pragma once
#include "Catan.hpp"
#include <string>
#include <vector>
#include <map>
#include "ResourceTypes.hpp"
#include "Buildable.hpp"
#include "DevelopmentCard.hpp"
#include "Tile.hpp"

using std::vector, std::string, std::map;

namespace ariel{
    class Catan;
    class Player
    {
        private:        // by default
            string name;
            int resources[5];       // holds the amount of each resource (index i := ResourceType(i+1))
            vector<size_t> roads;
            vector<size_t> settlements;     // holds board index of all settlements
            vector<Tile> tiles;     // holds the tiles that the player has settlements on
            bool currTurn;
            vector<DevelopmentCard*> developmentCards;
            int victoryPoints;
            // Catan catan;

        public:
            Player(string name);
            int placeSettlement(int index, Catan& catan);
            int placeRoad(int index, Catan& catan);
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
            int addVictoryPoints(int points);
            vector<Tile>& getTiles();
    };
}