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
    int Player::placeSettlement(size_t index, Board& board){
        if (currTurn == false){
            throw std::invalid_argument("Player tried to place a settlement when it's not his turn");
        }
        int status = catan.placeSettlement(*this, index);
        if(status == 0){
            settlements.push_back(index);
            settlementsNum.push_back(1);
        }
        return status;
    }
    string Player::getName(){
        return name;
    }
    int Player::numOfSettlements(){
        return settlements.size();
    }
    // void Player::placeRoad(vector<string> places, vector<int> placesNum, Board board);
    // void Player::buyDevelopmentCard();
    // void Player::printPoints();
    // void Player::trade(Player& player, const string& resourceSent, const string& resourceReceived, const int& amountSent, const int& amountReceived);
    void Player::rollDice(){
        int dice = rand() % 6 + 1 + rand() % 6 + 1;
        cout << "Dice rolled: " << dice << endl;
        if (dice == 7){
            // move robber
        }
        else{
            // give resources
        }
    }

    void Player::endTurn(Catan& catan){
        currTurn = false;
        catan.nextPlayer();
    }
    void Player::startTurn(){
        currTurn = true;
    }
}