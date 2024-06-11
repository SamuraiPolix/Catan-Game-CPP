
#include "Player.hpp"
#include "Tile.hpp"

namespace ariel {
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
        
    public:
        Buildable();
        Buildable(BuildableTypes type, Player& owner);

        void setSettlement(Player& owner);
        void setRoad(Player& owner);
        Player& getOwner() const;
        Tile& getTile() const;
        BuildableTypes getType() const;
    };
}