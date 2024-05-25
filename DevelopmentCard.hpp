#include <string>
#include <stdexcept>

using std::string, std::invalid_argument;

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
    public:
        virtual void use() = 0;
        virtual ~DevelopmentCard() = default;
};

// Factory Design Pattern for creating development cards
class DevelopmentCardFactory {
    public:
        static DevelopmentCard* createCard(CardType type);
};

/* All types of cards */ 

// Promotion Card (Abstract class for all Promotion cards)
class PromotionCard : public DevelopmentCard{
    public:
        virtual void use() = 0;
};

class RoadBuildingCard : public PromotionCard {
    public:
        void use() override;
};

class YearOfPlentyCard : public PromotionCard {
    public:
        void use() override;
};

class MonopolyCard : public PromotionCard {
    public:
        void use() override;
};

class KnightCard : public DevelopmentCard{
    public:
        void use() override;
};

class VictoryPointCard : public DevelopmentCard{
    public:
        void use() override;
};
