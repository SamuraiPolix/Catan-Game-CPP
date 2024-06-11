
#include "ResourceTypes.hpp"
#include "Player.hpp"
#include "Buildable.hpp"

namespace ariel {
    enum VertexPosition {
        TOP_LEFT = 0,
        TOP = 1,
        TOP_RIGHT = 2,
        BOTTOM_RIGHT = 3,
        BOTTOM = 4,
        BOTTOM_LEFT = 5
    };

    enum EdgePosition {
        TOP_LEFT = 0,
        TOP_RIGHT = 1,
        RIGHT = 2
        BOTTOM_RIGHT = 3,
        BOTTOM_LEFT = 4,
        LEFT = 5
    };

    // override edgePosition + - operators
    EdgePosition operator+(EdgePosition pos, int num);
    EdgePosition operator+(int num, EdgePosition pos);
    EdgePosition operator-(EdgePosition pos, int num);
    EdgePosition operator-(int num, EdgePosition pos);

    class Tile
    {
        // private members
            ResourceType resource;      // the resource the tile gives
            size_t diceNumber;      // number on tile that gives resources to players when rolled
            bool hasRobber;         // if there is a robber on the tile (no resources are given when rolled)
            vector<Player> players;     // the players that have a settlement or city on the tile (they get resources when the dice number matches the tile)
            Buildable hexVertices[6];       // the vertices of the tile - can be settlements, cities or nothing
            Buildable hexEdges[6];      // The edges of the tile - can be roads or nothing
        
        // private methods
            void initHexes();
            void initEdges();

        public:
            Tile(ResourceType resource, size_t number) : resource(resource), diceNumber(number), hasRobber(false) {initHexes(); initEdges();};
            void setResource(ResourceType resource);
            void setNumber(size_t number);
            void setRobber(bool hasRobber);
            void addPlayer(Player& player);
            void removePlayer(Player& player);

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
            Buildable& getVertex(VertexPosition pos) const;
            Buildable& getEdge(EdgePosition pos) const;
    };
}