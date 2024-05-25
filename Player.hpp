#include "Board.hpp"
#include <string>
#include <vector>

using std::vector, std::string;

namespace ariel{
    class Player
    {
        private:        // by default
            string name;
            vector<string> resources;
            vector<int> resourcesNum;
            vector<string> settlements;
            vector<int> settlementsNum;
            vector<string> roads;
            vector<int> roadsNum;

        public:
            Player(string name);
            void placeSettlement(vector<string> places, vector<int> placesNum, Board board);
            void placeRoad(vector<string> places, vector<int> placesNum, Board board);
            void buyDevelopmentCard();
            void printPoints();
            void trade(Player& player, const string& resourceSent, const string& resourceReceived, const int& amountSent, const int& amountReceived);
            void rollDice();
            void endTurn();
    };
}