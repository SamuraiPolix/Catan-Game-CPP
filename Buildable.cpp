#include "Buildable.hpp"
#include <string>

using std::string;

namespace ariel {
    Buildable::Buildable(){
        // this->tile = &tile;
        type = BuildableTypes::None;
        owner = NULL;
    }
    Buildable::Buildable(BuildableTypes type, Player& owner){
        // this->tile = &tile;
        this->type = type;
        this->owner = &owner;
    }
    void Buildable::setSettlement(Player& owner){
        type = Settlement;
        this->owner = &owner;
    }
    void Buildable::setRoad(Player& owner){
        type = Road;
        this->owner = &owner;
    }
    Player& Buildable::getOwner() const{
        return *owner;
    }
    Tile& Buildable::getTile() const{
        return *tile;
    }
    BuildableTypes Buildable::getType() const{
        return type;
    }
}