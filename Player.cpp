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
        for (int i = 0; i < 5; i++){
            resources[i] = 0;
        }
    }
    int Player::placeSettlement(size_t index, Board* board){
        // make sure its the player's turn
        if (currTurn == false){
            throw std::invalid_argument("Player tried to place a settlement when it's not his turn");
        }
        // make sure player has enough resources, if its not the first 2 settlements
        if (numOfSettlements() >= 2){
            if (resources[ResourceType::Wood-1] < 1 || resources[ResourceType::Brick-1] < 1 || resources[ResourceType::Sheep-1] < 1 || resources[ResourceType::Wheat-1] < 1){
                throw valid_resources("Player doesn't have enough resources (1 Wood, 1 Brick, 1 Sheep, 1 Wheat) to place a settlement\n");
            }
        }
        // place settlement
        int status = board->placeSettlement(*this, index);

        if(status == 0){
            settlements.push_back(index);
        }

        if (numOfSettlements() > 2){       // player pays for settlements after the first 2
            resources[ResourceType::Wood-1]--;
            resources[ResourceType::Brick-1]--;
            resources[ResourceType::Sheep-1]--;
            resources[ResourceType::Wheat-1]--;
        }
        return status;
    }
    string Player::getName() const{   
        return "\033[" + std::to_string(color) + "m" + name + "\033[0m";
    }
    int Player::numOfSettlements(){
        return settlements.size();
    }
    int Player::numOfRoads(){
        return roads.size();
    }
    int Player::placeRoad(size_t vertex1, size_t vertex2, Board* board){
        // make sure its the player's turn
        if (currTurn == false){
            throw std::invalid_argument("Player tried to place a road when it's not his turn");
        }
        // make sure player has enough resources, if its not the first 2 settlements
        if (numOfRoads() > 2){
            if (resources[ResourceType::Wood-1] < 1 || resources[ResourceType::Brick-1] < 1){
                throw valid_resources("Player doesn't have enough resources (1 Wood, 1 Brick) to place a road\n");
            }
        }
        // place road
        int status = board->placeRoad(*this, vertex1, vertex2);
        if(status == 0){
            roads.push_back({vertex1, vertex2});
        }

        if (numOfRoads() > 2){       // player pays for settlements after the first 2
            resources[ResourceType::Wood-1]--;
            resources[ResourceType::Brick-1]--;
        }
        return status;
    }
    size_t Player::buyDevelopmentCard(Catan& catan){
        if (currTurn == false){
            throw std::invalid_argument("Player tried to buy a development card when it's not his turn");
        }
        // check if player has enough resources
        if (ResourceType::Ore < 1 || ResourceType::Wheat < 1 || ResourceType::Sheep < 1){
            throw valid_resources("Player doesn't have enough resources (1 Ore, 1 Wheat, 1 Sheep) to buy a development card\n");
        }
        // remove resources
        resources[ResourceType::Ore-1]--;
        resources[ResourceType::Wheat-1]--;
        resources[ResourceType::Sheep-1]--;
        // add development card
        return catan.addDevelopmentCard(*this);
    }
    // void Player::printPoints();
    void Player::trade(Player& player, ResourceType resourceSent, ResourceType resourceReceived, const int& amountSent, const int& amountReceived){
        // make sure its the player's turn
        if (currTurn == false){
            throw std::invalid_argument("Player tried to trade when it's not his turn");
        }
        // make sure player has enough resources
        if (resources[resourceSent-1] < amountSent){
            throw valid_resources("Player doesn't have enough resources to trade\n");
        }
        // make sure other player has enough resources
        if (player.getResourceAmount(resourceReceived) < amountReceived){
            throw valid_resources("Other player doesn't have enough resources to trade\n");
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

    size_t Player::addDevelopmentCard(DevelopmentCard& card){
        developmentCards.push_back(&card);
        return developmentCards.size()-1;
    }

    int Player::useDevelopmentCard(size_t indexInHand){
        developmentCards[indexInHand]->use();
        return 0;
    }

    size_t Player::printDevelopmentCards(){
        for (size_t i = 0; i < developmentCards.size(); i++){
            cout << i << ". " << *developmentCards[i] << endl;
        }
        return developmentCards.size();
    }

    void Player::addTile(Tile& tile){
        tiles.push_back(tile);
    }

    // int Player::addTilesByIndex(size_t index){
    //     for (size_t i = 0; i < tiles.size(); i++){
    //         if (tiles[i].hasIndexVertex(index) == index){
    //             return -1;
    //         }
    //     }
    //     tiles.push_back(Tile(index));
    //     return 0;
    // }

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

    ostream& operator<<(ostream& os, const Player& player){
        os << player.getName() << ": " << endl;
        os << "- Victory Points: " << player.victoryPoints << endl;
        os << "- Resources: " << endl;
        for (size_t i = 0; i < 5; i++){
            cout << "  - " << getResourceName((ResourceType)(i+1)) << ": " << player.resources[i] << endl;
        }
        return os;
    }
}