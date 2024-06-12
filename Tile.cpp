#include "Tile.hpp"

namespace ariel{
    // edgePosition + - operators override
    EdgePosition operator+(EdgePosition pos, int num){
        return (EdgePosition)(((int)(pos + num)) % 6);
    }
    EdgePosition operator+(int num, EdgePosition pos){
        return (EdgePosition)(((int)(pos + num)) % 6);
    }
    EdgePosition operator-(EdgePosition pos, int num){
        return (EdgePosition)(((int)(pos-num)) % 6);
    }
    EdgePosition operator-(int num, EdgePosition pos){
        return (EdgePosition)(((int)(num - pos)) % 6);
    }
    VertexPosition operator+(VertexPosition pos, int num){
        return (VertexPosition)(((int)(pos + num)) % 6);
    }
    VertexPosition operator+(int num, VertexPosition pos){
        return (VertexPosition)(((int)(pos + num)) % 6);
    }
    VertexPosition operator-(VertexPosition pos, int num){
        return (VertexPosition)(((int)(pos - num)) % 6);
    }
    VertexPosition operator-(int num, VertexPosition pos){
        return (VertexPosition)(((int)(num - pos)) % 6);
    }

    void initHexVertices(vector<Buildable>& hexVertices){
        for (size_t i = 0; i < hexVertices.size(); i++){
            hexVertices[i] = Buildable();
        }
    }
    void initHexEdges(vector<Buildable>& hexEdges){
        for (size_t i = 0; i < hexEdges.size(); i++){
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
                players.erase(players.begin() + ind);
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
    Buildable& Tile::getHexVertex(VertexPosition pos) const{
        return hexVertices[pos];
    }
    Buildable& Tile::getHexEdge(EdgePosition pos) const{
        return hexEdges[pos];
    }
    int Tile::setSettlementAt(VertexPosition pos, Player& player){
        if (hexVertices[pos].getType() == BuildableTypes::None){
            hexVertices[pos] = Buildable(BuildableTypes::Settlement, player);

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
            hexEdges[pos] = Buildable(BuildableTypes::Road, player);
            return 0;
        }
        return -1;
    }
}