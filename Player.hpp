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
            vector<Buildable> roads;
            vector<Buildable> settlements;
            

        public:
            Player(string name){
                this->name = name;
                resources = {{ResourceType::Wood, 0}, {ResourceType::Brick, 0}, {ResourceType::Sheep, 0}, {ResourceType::Wheat, 0}, {ResourceType::Ore, 0}};
                settlements = {};
                settlementsNum = {};
                roads = {};
                roadsNum = {};
            }
            void placeSettlement(vector<string> places, vector<int> placesNum, Board board);
            void placeRoad(vector<string> places, vector<int> placesNum, Board board);
            void buyDevelopmentCard();
            void printPoints();
            void trade(Player& player, const string& resourceSent, const string& resourceReceived, const int& amountSent, const int& amountReceived);
            void rollDice();
            void endTurn();
            string getName();
    };
}