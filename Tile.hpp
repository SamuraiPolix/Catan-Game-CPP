#pragma once
#include "Types.hpp"
#include "Player.hpp"
#include "Buildable.hpp"
#include <vector>
#include <iostream>

using std::vector, std::ostream;

namespace ariel {
    class Buildable;
    class Tile
    {
        // private members
            ResourceType resource;      // the resource the tile gives
            size_t diceNumber;      // number on tile that gives resources to players when rolled
            bool hasRobber;         // if there is a robber on the tile (no resources are given when rolled)
            vector<Player> players;     // the players that have a settlement or city on the tile (they get resources when the dice number matches the tile)
            Buildable* hexVertices[6];       // the vertices of the tile - can be settlements, cities or nothing
            Buildable* hexEdges[6];      // The edges of the tile - can be roads or nothing
            size_t x, y;        // the position of the tile on the board
        // private methods
            // void initHexVertices();
            // void initHexEdges();

        public:
            Tile() : x(0), y(0), resource(ResourceType::Desert), diceNumber(0), hasRobber(false) {};
            Tile(size_t _x, size_t _y, ResourceType _resource, size_t _number) : x(_x), y(_y), resource(_resource), diceNumber(_number), hasRobber(false) {};
            void setResource(ResourceType resource);
            void setNumber(size_t number);
            void setRobber(bool hasRobber);
            void addPlayer(Player& player);
            void removePlayer(Player& player);

            friend ostream& operator<<(ostream& os, const Tile& tile);

            void setVertexAtPos(size_t pos, Buildable* buildable);
            void setEdgeAtPos(size_t pos, Buildable* buildable);

            /*
             * Sets the vertex at the given position to a settlement.
             * Returns 0 if the vertex was empty and the settlement was placed successfully.
             * Returns -1 if the vertex is already taken.
            */
            int setSettlementAt(VertexPosition pos, Player& player);

            /*
             * Sets the edge at the given position to a road.
             * Returns 0 if the edge was empty and the road was placed successfully.
             * Returns -1 if the edge is already taken.
             * @note: This doesn't check if the player has a building (settlement, city or road) near
             *       - this should be checked in the Board class.
            */
            int setRoadAt(EdgePosition pos, Player& player);

            ResourceType getResource() const;
            size_t getNumber() const;
            bool getRobber() const;
            vector<Player> getPlayers() const;
            Buildable* getVertex(VertexPosition pos);
            Buildable* getEdge(EdgePosition pos);
            bool isVertexOwner(VertexPosition pos, Player& player);
            bool isEdgeOwner(EdgePosition pos, Player& player);
            size_t getX() const {return x;};
            size_t getY() const {return y;};
    };
}