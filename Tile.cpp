#include "Tile.hpp"

namespace ariel{

    ostream& operator<<(std::ostream& os, const Tile& tile){
        os << tile.resource << " (" << tile.diceNumber << ") ";
        return os;
    }
    // void Tile::initHexVertices(){
    //     for (size_t i = 0; i < 6; i++){
    //         hexVertices[i] = Buildable();
    //     }
    // }
    // void Tile::initHexEdges(){
    //     for (size_t i = 0; i < 6; i++){
    //         hexEdges[i] = Buildable();
    //     }
    // }

    void Tile::setVertexAtPos(size_t pos, Buildable* buildable){
        hexVertices[pos] = buildable;
    }
    void Tile::setEdgeAtPos(size_t pos, Buildable* buildable){
        hexEdges[pos] = buildable;
    }
    void Tile::setResource(ResourceType resource){
        this->resource = resource;
    }
    void Tile::setNumber(size_t number){
        this->diceNumber = number;
    }
    void Tile::setRobber(bool hasRobber) {
        this->hasRobber = hasRobber;
    }
    void Tile::addPlayer(Player& player){
        players.push_back(player);
    }
    void Tile::removePlayer(Player& player){
        for (size_t ind = 0; ind < players.size(); ind++){
            if (players[ind].getName() == player.getName()){
                players.erase(players.begin() + (int)ind);
                break;      // found the player, no need to continue
            }
        }
    }
    ResourceType Tile::getResource() const{
        return this->resource;
    }
    size_t Tile::getNumber() const{
        return this->diceNumber;
    }
    bool Tile::getRobber() const{
        return this->hasRobber;
    }
    vector<Player> Tile::getPlayers() const{
        return this->players;
    }
    Buildable* Tile::getVertex(VertexPosition pos){
        return hexVertices[pos];
    }
    Buildable* Tile::getEdge(EdgePosition pos){
        return hexEdges[pos];
    }
    bool Tile::isVertexOwner(VertexPosition pos, Player& player){
        if (hexVertices[pos]->getOwner() != NULL)
            return hexVertices[pos]->getOwner()->getName() == player.getName();
        else
            return false;
    }
    bool Tile::isEdgeOwner(EdgePosition pos, Player& player){
        if (hexEdges[pos]->getOwner() != NULL)
            return hexEdges[pos]->getOwner()->getName() == player.getName();
        else
            return false;
    }
    bool Tile::hasIndexVertex(size_t index){
        for (size_t i = 0; i < 6; i++){
            if (hexVertices[i]->getIndex() == index){
                return true;
            }
        }
        return false;
    }
    int Tile::setSettlementAt(VertexPosition pos, Player& player){
        std::cout << "TYPE: " << hexVertices[pos]->getType() << "\n";
        std::cout << "Land: " << this->getResource() << "\n";
        std::cout << "NUM: " << this->getNumber() << "\n";
        if (hexVertices[pos]->getType() == BuildableTypes::None){
            hexVertices[pos]->setSettlement(player);

            // add player to list if is not in it already
            if (this->players.size() == 0){
                this->players.push_back(player);
            }
            else{
                for (size_t i = 0; i < this->players.size(); i++){
                    if (this->players[i].getName() == player.getName()){
                        return 0;
                    }
                }
                this->players.push_back(player);
                return 0;
            }
            return 0;
        }
        return -1;
    }

    int Tile::setRoadAt(EdgePosition pos, Player& player){
        std::cout << "TYPE: " << hexEdges[pos]->getType() << "\n";
        std::cout << "Land: " << this->getResource() << "\n";
        std::cout << "NUM: " << this->getNumber() << "\n";
        if (hexEdges[pos]->getType() == BuildableTypes::None){
            hexEdges[pos]->setRoad(player);
            return 0;
        }
        return -1;
    }
}