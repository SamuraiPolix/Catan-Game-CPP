#include "Player.hpp"
#include "Types.hpp"
#include <iostream>

using std::vector, std::string, std::map, std::cout, std::endl;

namespace ariel{
    // static vars
    Color Player::colors[3] = {Color::Red, Color::Green, Color::Blue};
    int Player::playerCounter = 0;

    // functions
    Player::Player(string name) {
        this->name = name;
        // resources = {};
        settlements = {};
        roads = {};
        tiles = {};
        currTurn = false;
        developmentCards = {};
        victoryPoints = 0;
        color = colors[playerCounter++];
    }
    int Player::placeSettlement(size_t index, Catan& catan){
        // make sure its the player's turn
        if (currTurn == false){
            throw std::invalid_argument("Player tried to place a settlement when it's not his turn");
        }
        // make sure player has enough resources, if its not the first 2 settlements
        if (numOfSettlements() >= 2){
            if (resources[ResourceType::Wood-1] < 1 || resources[ResourceType::Brick-1] < 1 || resources[ResourceType::Sheep-1] < 1 || resources[ResourceType::Wheat-1] < 1){
                throw std::invalid_argument("Player doesn't have enough resources (1 Wood, 1 Brick, 1 Sheep, 1 Wheat) to place a settlement\n");
            }
        }
        // place settlement
        int status = catan.placeSettlement(*this, index);

        if(status == 0){
            settlements.push_back(index);
        }

        if (numOfSettlements() >= 2){       // player pays for settlements after the first 2
            resources[ResourceType::Wood-1]--;
            resources[ResourceType::Brick-1]--;
            resources[ResourceType::Sheep-1]--;
            resources[ResourceType::Wheat-1]--;
        }
        return status;
    }
    string Player::getName(){   
        return "\033[" + std::to_string(color) + "m" + name + "\033[0m";
    }
    int Player::numOfSettlements(){
        return settlements.size();
    }
    int Player::placeRoad(size_t index, Catan& catan){
        // // make sure its the player's turn
        // if (currTurn == false){
        //     throw std::invalid_argument("Player tried to place a road when it's not his turn");
        // }
        // // make sure player has enough resources
        // if (resources[ResourceType::Wood-1] < 1 || resources[ResourceType::Brick-1] < 1){
        //     throw std::invalid_argument("Player doesn't have enough resources (1 Wood, 1 Brick) to place a road\n");
        // }
        // // place road
        // int status = catan.placeRoad(*this, index);
    int status = 1;
        // if(status == 0){
        //     roads.push_back(index);
        //     roadsNum.push_back(1);
        //     // building was successful, remove resources
        //     resources[ResourceType::Wood-1]--;
        //     resources[ResourceType::Brick-1]--;
        // }
        return status;
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
    void Player::trade(Player& player, ResourceType resourceSent, ResourceType resourceReceived, const int& amountSent, const int& amountReceived){
        // make sure its the player's turn
        if (currTurn == false){
            throw std::invalid_argument("Player tried to trade when it's not his turn");
        }
        // make sure player has enough resources
        if (resources[resourceSent-1] < amountSent){
            throw std::invalid_argument("Player doesn't have enough resources to trade\n");
        }
        // make sure other player has enough resources
        if (player.getResourceAmount(resourceReceived) < amountReceived){
            throw std::invalid_argument("Other player doesn't have enough resources to trade\n");
        }
        // remove resources
        resources[resourceSent-1] -= amountSent;
        player.addResource(resourceReceived, -amountReceived);
        // add resources
        resources[resourceReceived-1] += amountReceived;
        player.addResource(resourceSent, amountSent);
    }
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

    int Player::addVictoryPoints(size_t points){
        victoryPoints += points;
        return victoryPoints;
    }

    vector<Tile>& Player::getTiles(){
        return tiles;
    }

    Color Player::getColor(){
        return color;
    }
}