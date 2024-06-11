#include "Player.hpp";

using std::vector, std::string;

namespace ariel{
    Player::Player(string name) {
        this->name = name;
        resources = {"wood", "brick", "sheep", "wheat", "ore"};
        resourcesNum = {0, 0, 0, 0, 0};
        settlements = {};
        settlementsNum = {};
        roads = {};
        roadsNum = {};
    }
    void Player::placeSettlement(vector<string> places, vector<int> placesNum, Board board){
        for (int i = 0; i < places.size(); i++){
            if (board.get[placesNum[i]][places[i]] == "Settlement"){
                throw std::invalid_argument("There is already a settlement in this place.");
            }
            board.board[placesNum[i]][places[i]] = "Settlement";
        }
    }
    string Player::getName(){
        return name;
    }
    // void Player::placeRoad(vector<string> places, vector<int> placesNum, Board board);
    // void Player::buyDevelopmentCard();
    // void Player::printPoints();
    // void Player::trade(Player& player, const string& resourceSent, const string& resourceReceived, const int& amountSent, const int& amountReceived);
    // void Player::rollDice();
    // void Player::endTurn();
}