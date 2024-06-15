#include "Tile.hpp"

namespace ariel{

    ostream& operator<<(std::ostream& os, const Tile& tile){
        os << tile.resource << " (" << tile.diceNumber << ") ";
        return os;
    }
    void Tile::initHexVertices(){
        for (size_t i = 0; i < 6; i++){
            hexVertices[i] = Buildable();
        }
    }
    void Tile::initHexEdges(){
        for (size_t i = 0; i < 6; i++){
            hexEdges[i] = Buildable();
        }
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
    Buildable& Tile::getVertex(VertexPosition pos){
        return hexVertices[pos];
    }
    Buildable& Tile::getEdge(EdgePosition pos){
        return hexEdges[pos];
    }
    int Tile::setSettlementAt(VertexPosition pos, Player& player){
        std::cout << "TYPE: " << hexVertices[pos].getType() << "\n";
        if (hexVertices[pos].getType() == BuildableTypes::None){
            hexVertices[pos] = Buildable(BuildableTypes::Settlement, player, pos);

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
        if (hexEdges[pos].getType() == BuildableTypes::None){
            hexEdges[pos] = Buildable(BuildableTypes::Road, player, pos);
            return 0;
        }
        return -1;
    }
}