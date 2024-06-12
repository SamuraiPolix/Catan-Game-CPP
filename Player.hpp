#include "Board.hpp"
#include <string>
#include <vector>
#include <map>
#include "ResourceTypes.hpp"
#include "Buildable.hpp"

using std::vector, std::string, std::map;

namespace ariel{
    class Player
    {
        private:        // by default
            string name;
            map<ResourceType, int> resources;
            vector<size_t> roads;
            vector<size_t> settlements;     // holds board index of all settlements
            bool currTurn;
            

        public:
            Player(string name);
            int placeSettlement(size_t index, Board& board);
            int placeRoad(size_t index, Board& board);
            void buyDevelopmentCard();
            void printPoints();
            void trade(Player& player, const string& resourceSent, const string& resourceReceived, const int& amountSent, const int& amountReceived);
            void rollDice();
            void endTurn();
            void startTurn();
            string getName();
            int numOfSettlements();
            int numOfRoads();
    };
}