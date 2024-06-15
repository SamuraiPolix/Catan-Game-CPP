#include "Buildable.hpp"
#include <string>

using std::string;

namespace ariel {
    Buildable::Buildable(){
        // this->tile = &tile;
        type = BuildableTypes::None;
        owner = NULL;
        pos = 0;
    }
    Buildable::Buildable(BuildableTypes type, Player& owner, size_t pos){
        // this->tile = &tile;
        this->type = type;
        this->owner = &owner;
        this->pos = pos;
    }
    void Buildable::setSettlement(Player& owner){
        type = Settlement;
        this->owner = &owner;
    }
    void Buildable::setRoad(Player& owner){
        type = Road;
        this->owner = &owner;
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
    ostream& operator<<(ostream& os, const Buildable& buildable){
        if (buildable.owner != NULL){
            // some one owns this buildable - with a settlement or road, print the type and colorize with player's color
            if (buildable.type == BuildableTypes::Settlement){
                os << "STL";
            }
            else if (buildable.type == BuildableTypes::City){
                os << "CTY";
            }
        }
        else {
            // os << buildable.pos;
        }
        return os;
    }
}