
#pragma once
#include <iostream>
#include "Types.hpp"

using std::ostream;

namespace ariel {
    class Player;
    class Tile;

    enum BuildableTypes{
        None = 0,
        Road = 1,
        Settlement = 2,
        City = 3
    };

    class Buildable
    {
        BuildableTypes type;
        Player* owner;
        Tile* tile;
        size_t pos;
        
    public:
        Buildable();
        Buildable(BuildableTypes type, Player& owner, size_t pos);

        void setSettlement(Player& owner);
        void setRoad(Player& owner);
        Player* getOwner() const;
        Tile& getTile() const;
        BuildableTypes getType() const;

        friend ostream& operator<<(ostream& os, const Buildable& buildable);
    };
}