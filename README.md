# Catan - Classes and Inheritance - C++ Assignment #4
#### (Systems Programming B @ Ariel University)
#### Author: Samuel Lazareanu (sam.lazareanu@gmail.com)

[Link to requirements](ASSIGNMENT.md)


**The Settlers of Catan** is a board game for 3 to 4 players that combines strategic thinking, resource management, and trading skills. The objective of the game is to be the first player to accumulate 10 victory points. The full game instructions can be found [here](https://www.hakubia.com/wp-content/uploads/2021/01/%D7%A7%D7%98%D7%90%D7%9F.pdf). In this assignment, I implemented a simpler version of the game for 3 players (some rules were changed).

## Game Rules

The game consists of a board with 19 land plots surrounded by the sea. Each land provides a resource (except the desert). The resources are:
 - **Ore**
- **Wheat**
- **Sheep**
- **Wood**
- **Brick**
- Desert - Not a resource, but a land type

Each land is assigned a number between 2 and 12.

### Cards, Settlements, Cities, and Resources

Players can use resources to buy development cards, settlements, cities, and roads.

Used iheritance to create the DevelopmentCards. The DevelopmentCard class is an abstract class that has a pure virtual function called use(). The PromotionCard class is a subclass of DevelopmentCard and has 3 subclasses: RoadBuilding, YearOfPlenty, and Monopoly. The KnightCard and VictoryPointCard classes are subclasses of DevelopmentCard.
- **Development Card**: Costs 1 wheat, 1 ore, and 1 sheep. There are 3 types of development cards:
  1. **Progress Card**: Provides a benefit to the player (then the card is discarded). Examples include:
     - **Monopoly**: The player chooses a resource type, and all other players must give them all of that resource.
     - **Road Building**: The player can build 2 roads for free.
     - **Year of Plenty**: The player receives 2 resource cards of their choice from the bank.
  2. **Knight Card**: A player with 3 of these cards receives the largest army card worth 2 victory points (the points are lost if another player has more knight cards).
  3. **Victory Point Card**: Gies 1 additional victory point, doesn't need to be played (4 cards available).

- **Building**:
  1. **Road**: Costs 1 brick and 1 wood. A road can only connect to a player's settlement, city, or another road.
  2. **Settlement**: Costs 1 brick, 1 wood, 1 sheep, and 1 wheat. Grants 1 victory point. A settlement can only be built on an empty plot and must be at least 2 plots away from another settlement or city. Settlements give resources based on the numbers and resources assignment to the surrounding lands, on dice rolls.

- **Resources**: Players gain resources from land plots. When a player rolls the dice, all players receive resources based on the number rolled and the plots adjacent to their settlements or cities.

- **Trading**: Players can trade resources with each other.

### Gameplay

Each player starts with 2 settlements and 2 roads, giving them 2 victory points. Players also receive initial resources based on their second settlement's location.

Players take turns in the following order:
1. **Roll the Dice**: The player rolls 2 dice. All players receive resources based on the roll.
    1. **Build Settlement**: If a player has enough resources, they can build a settlement.
    2. **Build Road**: If a player has enough resources, they can build a road.
    3. **Buy Development Card**: If a player has enough resources, they can buy a development card.
    4. **Use Development Card**: If a player has a development card, they can use it.
    5. **Trade**: Players can trade resources with each other.
    6. **End Turn**: The player ends their turn.
2. **Use Development Card**: If a player has a development card, they can use it.

If a player rolls a 7, any player with more than 7 resource cards must discard half of them to the bank.

### Ending the Game

The game ends when a player reaches 10 or more victory points.

---

## Implementation

### Main Classes and their Responsibilities

- **Catan**: The main class managing the game - holds the players, board and cards. Makes sure all actions are legal.
- **Player**: Represents a player, managing their resources, buildings, and stats.
- **Board**: Represents the game board, containing tiles and managing the layout.
    - **Tile**: Represents individual land plots, holding information about the resource type and number and the surrounding vertices and edges.
        - **Buildable**: An interface or abstract class for buildable objects (roads, settlements, cities).
            - **BuildableVertex**: Represents a vertex that can hold a settlement or city.
            - **BuildableEdge**: Represents an edge that can hold a road.
- **DevelopmentCard**: Abstract class for all card types, has factory method `create_card()`. Subclasses:
    - **PromotionCard**: Abstract subclass with specific types:
        - **RoadBuilding**: Allows the player to build 2 roads.
        - **YearOfPlenty**: Allows the player to draw 2 resource cards from the bank.
        - **Monopoly**: Allows the player to claim all of a specific resource from other players.
    - **KnightCard**: Allows the player to move the robber.
    - **VictoryPointCard**: Grants 1 victory point.

### Board Structure

The board consists of tiles, each holding 6 VerticeBuildables and 6 EdgeBuildables. The board is indexed by vertices and edges.
![Board indexes planning](https://github.com/SamuraiPolix/Catan-Game-CPP/assets/52662032/69ef7f6c-4b21-4719-a26b-7bcf81effd0a)
![Board print example](https://github.com/SamuraiPolix/Catan-Game-CPP/assets/52662032/e6d051f3-35e5-4fcb-9427-ee2d2e70fbc5)



## Usage
1. Clone the repository.

Full game:

- `make catan` - compiles the project, creating exec file `catan` to run the game.
- `./catan` - runs the game.

Basic usage example:

A basic usage example can be found inside the Demo.cpp file.
- `make demo` -     run using `./demo`  (simple test)




### Tests

Tests:
- `make test` -     run using `./test`  (advanced doctest)
- `make tidy` -     makes sure the code is clean
- `make valgrind` - makes sure there are no memory leaks/problems.


#### clang-tidy and valgrind
Before submitting we ran clang-tidy to make sure the code is written well, and valgrind to make sure there are no memory errors or leaks.

#### Test.cpp
This file includes tests on everything implemented in the Tree class. It tests the methods, the iterators, and the operators.
