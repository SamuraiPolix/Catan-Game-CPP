#include "Buildable.hpp"
#include <string>

using std::string;

namespace ariel {
    Buildable::Buildable(){
        // this->tile = &tile;
        type = BuildableTypes::None;
        owner = NULL;
        index = 0;
        pos = 0;
    }
    Buildable::Buildable(size_t index){
        // this->tile = &tile;
        type = BuildableTypes::None;
        owner = NULL;
        this->index = index;
        pos = 0;
    }
    Buildable::Buildable(BuildableTypes type, Player& owner, size_t index){
        // this->tile = &tile;
        this->type = type;
        this->owner = &owner;
        this->index = index;
        pos = 0;
    }
    BuildableVertex::BuildableVertex() : Buildable() {};
    BuildableVertex::BuildableVertex(size_t index) : Buildable(index) {};
    BuildableVertex::BuildableVertex(BuildableTypes type, Player& owner, size_t index) : Buildable(type, owner, index) {};
    BuildableEdge::BuildableEdge() : Buildable() {};
    BuildableEdge::BuildableEdge(size_t index) : Buildable(index) {};
    BuildableEdge::BuildableEdge(BuildableTypes type, Player& owner, size_t index) : Buildable(type, owner, index) {};

    void BuildableVertex::setSettlement(Player& owner){
        type = Settlement;
        this->owner = &owner;
    }
    void BuildableEdge::setRoad(Player& owner){
        type = Road;
        this->owner = &owner;
    }
    void BuildableEdge::setSettlement(Player& owner){
        throw std::invalid_argument("Failed to place settlement at BuildableEdge!\nMake sure you use BuildableVertex for settlements.\n");
    }
    void BuildableVertex::setRoad(Player& owner){
        throw std::invalid_argument("Failed to place road at BuildableVertex!\nMake sure you use BuildableEdge for roads.!\n");
    }
    void Buildable::setPos(size_t pos){
        this->pos = pos;
    }
    size_t Buildable::getPos() const {
        return pos;
    }
    Player* Buildable::getOwner() const{
        return owner;
    }
    Tile& Buildable::getTile() const{
        return *tile;
    }
    BuildableTypes Buildable::getType() const{
        return type;
    }
    size_t Buildable::getIndex() const{
        return index;
    }
    ostream& operator<<(ostream& os, const BuildableVertex& buildable){
        if (buildable.owner != NULL){
            os << "\033["<< buildable.owner->getColor() << "m ";
            // Used it before - realized its better to just print the index of the vertex
            // if (buildable.type == BuildableTypes::Settlement){
            //     os << "STL";
            // }
            // else if (buildable.type == BuildableTypes::City){
            //     os << "CTY";
            // }
        }
        os << buildable.index;
        os << "\033[0m";
        return os;
    }
    ostream& operator<<(ostream& os, const BuildableEdge& buildable){
        if (buildable.owner != NULL){
            os << "\033["<< buildable.owner->getColor() << "m ";
        }
        switch(buildable.pos){
            case EdgePosition::EDGE_LEFT:
            case EdgePosition::EDGE_RIGHT: os << "|"; break;
            case EdgePosition::EDGE_BOTTOM_LEFT:
            case EdgePosition::EDGE_TOP_RIGHT: os << "\\"; break;
            case EdgePosition::EDGE_BOTTOM_RIGHT:
            case EdgePosition::EDGE_TOP_LEFT: os << "/"; break;
            default: throw invalid_argument("Invalid position to print!\n");
        }
        os << "\033[0m";
        return os;
    }
}