/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

#pragma once
#include <string>
#include <stdexcept>
#include <iostream>


using std::string, std::invalid_argument;

namespace ariel{
    class Player;
    class Catan;
    // Enum to make cards creation organized
    enum CardType {
        Promotion = 10,
            RoadBuilding = 11,        // player can place 2 roads as if they just built them
            YearOfPlenty = 12,        // the player can draw 2 resource cards of their choice from the bank
            Monopoly = 13,            // player can claim all resource cards of a specific declared type
        Knight = 20,           // lets the player move the robber (only 3 cards)
        VictoryPoint = 30       // 1 additional Victory Point is added to the owners total and doesn't need to be played to win (4 cards)
    };

    // Abstract class for all developments cards
    class DevelopmentCard {
        protected:
            CardType type;
            Player* owner;
            Catan* game;
        public:
            virtual void use() = 0;     // make func and class abstract - must implement
            DevelopmentCard(CardType type, Catan* game) : type(type), owner(nullptr), game(game) {};
            // virtual ~DevelopmentCard() = default;
            CardType getType() const { return type; }
            void setOwner(Player* owner) { this->owner = owner; }
            friend std::ostream& operator<<(std::ostream &out, const DevelopmentCard &card);
    };

    // Factory Design Pattern for creating development cards
    class DevelopmentCardFactory {
        public:
            static DevelopmentCard* createCard(CardType type, Catan* game);
    };

    /* All types of cards */ 

    // Promotion Card (Abstract class for all Promotion cards)
    class PromotionCard : public DevelopmentCard{
        public:
            PromotionCard(CardType type, Catan* game) : DevelopmentCard(type, game) {};
            virtual void use() = 0;     // make func and class abstract - must implement
            friend std::ostream& operator<<(std::ostream &out, const PromotionCard &card);
    };

    class RoadBuildingCard : public PromotionCard {
        public:
            RoadBuildingCard(CardType type, Catan* game) : PromotionCard(type, game) {};
            void use() override;
            friend std::ostream& operator<<(std::ostream &out, const RoadBuildingCard &card);
    };

    class YearOfPlentyCard : public PromotionCard {
        public:
            YearOfPlentyCard(CardType type, Catan* game) : PromotionCard(type, game) {};
            void use() override;
            friend std::ostream &operator<<(std::ostream &out, const YearOfPlentyCard &card);
    };

    class MonopolyCard : public PromotionCard {
        public:
            MonopolyCard(CardType type, Catan* game) : PromotionCard(type, game) {};
            void use() override;
            friend std::ostream &operator<<(std::ostream &out, const MonopolyCard &card);
    };

    class KnightCard : public DevelopmentCard{
        public:
            KnightCard(CardType type, Catan* game) : DevelopmentCard(type, game) {};
            void use() override;
            friend std::ostream &operator<<(std::ostream &out, const KnightCard &card);
    };

    class VictoryPointCard : public DevelopmentCard{
        public:
            VictoryPointCard(CardType type, Catan* game) : DevelopmentCard(type, game) {};
            void use() override;
            friend std::ostream &operator<<(std::ostream &out, const VictoryPointCard &card);
    };
}
