
#pragma once
#include <iostream>
#include "Types.hpp"
#include "Player.hpp"

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
    protected:      // to allow access for inheriting classes
        BuildableTypes type;
        Player* owner;
        Tile* tile;
        size_t index;
        size_t pos;
        
    public:
        Buildable();
        Buildable(size_t index);
        Buildable(BuildableTypes type, Player& owner, size_t index);

        virtual void setSettlement(Player& owner) = 0;
        virtual void setRoad(Player& owner) = 0;
        void setPos(size_t pos);
        size_t getPos() const;
        Player* getOwner() const;
        Tile& getTile() const;
        BuildableTypes getType() const;
        size_t getIndex() const;

        // friend ostream& operator<<(ostream& os, const Buildable& buildable);
    };

    class BuildableVertex : public Buildable
    {
    public:
        BuildableVertex();
        BuildableVertex(size_t index);
        BuildableVertex(BuildableTypes type, Player& owner, size_t index);
        void setSettlement(Player& owner);
        void setRoad(Player& owner);
        friend ostream& operator<<(ostream& os, const BuildableVertex& buildable);
    };

    class BuildableEdge : public Buildable
    {
    public:
        BuildableEdge();
        BuildableEdge(size_t index);
        BuildableEdge(BuildableTypes type, Player& owner, size_t index);
        void setSettlement(Player& owner);
        void setRoad(Player& owner);
        friend ostream& operator<<(ostream& os, const BuildableEdge& buildable);
    };
}