#include "Player.hpp";
#include "ResourceTypes.hpp";
#include <iostream>

using std::vector, std::string, std::map, std::cout, std::endl;

namespace ariel{
    Player::Player(string name) {
        this->name = name;
        // resources = {};
        settlements = {};
        roads = {};
        tiles = {};
        currTurn = false;
        developmentCards = {};
        victoryPoints = 0;
    }
    int Player::placeSettlement(int index, Catan& catan){
        // make sure its the player's turn
        if (currTurn == false){
            throw std::invalid_argument("Player tried to place a settlement when it's not his turn");
        }
        // make sure player has enough resources
        if (resources[ResourceType::Wood-1] < 1 || resources[ResourceType::Brick-1] < 1 || resources[ResourceType::Sheep-1] < 1 || resources[ResourceType::Wheat-1] < 1){
            throw std::invalid_argument("Player doesn't have enough resources (1 Wood, 1 Brick, 1 Sheep, 1 Wheat) to place a settlement\n");
        }
        // place settlement
        int status = catan.placeSettlement(*this, index);

        if(status == 0){
            settlements.push_back(index);
            // building was successful, remove resources
            resources[ResourceType::Wood-1]--;
            resources[ResourceType::Brick-1]--;
            resources[ResourceType::Sheep-1]--;
            resources[ResourceType::Wheat-1]--;
        }
        return status;
    }
    string Player::getName(){
        return name;
    }
    int Player::numOfSettlements(){
        return settlements.size();
    }
    void Player::placeRoad(int index, Catan& catan){
        // // make sure its the player's turn
        // if (currTurn == false){
        //     throw std::invalid_argument("Player tried to place a road when it's not his turn");
        // }
        // // make sure player has enough resources
        // if (resources[ResourceType::Wood-1] < 1 || resources[ResourceType::Brick-1] < 1){
        //     throw std::invalid_argument("Player doesn't have enough resources (1 Wood, 1 Brick) to place a road\n");
        // }
        // // place road
        int status = catan.placeRoad(*this, index);

        // if(status == 0){
        //     roads.push_back(index);
        //     roadsNum.push_back(1);
        //     // building was successful, remove resources
        //     resources[ResourceType::Wood-1]--;
        //     resources[ResourceType::Brick-1]--;
        // }
        // return status;
    }
    void Player::buyDevelopmentCard(Catan& catan){
        if (currTurn == false){
            throw std::invalid_argument("Player tried to buy a development card when it's not his turn");
        }
        // check if player has enough resources
        if (ResourceType::Ore < 1 || ResourceType::Wheat < 1 || ResourceType::Sheep < 1){
            throw std::invalid_argument("Player doesn't have enough resources (1 Ore, 1 Wheat, 1 Sheep) to buy a development card\n");
        }
        // remove resources
        resources[ResourceType::Ore-1]--;
        resources[ResourceType::Wheat-1]--;
        resources[ResourceType::Sheep-1]--;
        // add development card
        catan.addDevelopmentCard(*this);
    }
    // void Player::printPoints();
    // void Player::trade(Player& player, const string& resourceSent, const string& resourceReceived, const int& amountSent, const int& amountReceived);
    void Player::rollDice(Catan& catan){
        // make sure its the player's turn
        if (currTurn == false){
            throw std::invalid_argument("Player tried to roll the dice when it's not his turn");
        }
        int dice = rand() % 6 + 1 + rand() % 6 + 1;
        cout << "Dice rolled: " << dice << endl;
        if (dice == 7){
            // move robber
        }
        else{
            catan.giveResources(dice);
        }
    }

    void Player::endTurn(Catan& catan){
        currTurn = false;
        catan.nextPlayer();
    }
    void Player::startTurn(){
        currTurn = true;
    }

    int Player::getResourceAmount(ResourceType resource){
        return resources[resource-1];
    }

    void Player::addDevelopmentCard(DevelopmentCard& card){
        developmentCards.push_back(&card);
    }

    void Player::addTile(Tile& tile){
        tiles.push_back(tile);
    }

    void Player::addResource(ResourceType resource, int amount){
        resources[resource-1] += amount;
    }

    int Player::getVictoryPoints(){
        return victoryPoints;
    }

    int Player::addVictoryPoints(int points){
        victoryPoints += points;
    }

    vector<Tile>& Player::getTiles(){
        return tiles;
    }
}