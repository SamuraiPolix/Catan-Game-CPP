#include "DevelopmentCard.hpp"

namespace ariel{
    DevelopmentCard* DevelopmentCardFactory::createCard(CardType type){
        switch (type)
        {
        case Promotion:
            throw std::invalid_argument("Promotion card by itself cannot be created, please specify the type of promotion card you want.");
            break;
        case RoadBuilding:
            return new RoadBuildingCard();
            break;
        case YearOfPlenty:
            return new YearOfPlentyCard();
            break;
        case Monopoly:
            return new MonopolyCard();
            break;
        case Knight:
            return new KnightCard();
            break;
        case VictoryPoint:
            return new VictoryPointCard();
            break;
        default:
            throw std::invalid_argument("Invalid card type.");
            break;
        }
        return NULL;
    }

    // TODO add return int to all uses - return status
    void RoadBuildingCard::use(){
        int x = 0;
    }

    void YearOfPlentyCard::use(){
        int x = 0;

    }

    void MonopolyCard::use(){
        int x = 0;

    }

    void KnightCard::use(){
        int x = 0;

    }

    void VictoryPointCard::use(){
        int x = 0;

    }

    // Overloading the << operator for each card type
    std::ostream& operator<<(std::ostream &out, const VictoryPointCard &card){
        return out << "Victory Point Card";
    }

    std::ostream& operator<<(std::ostream &out, const KnightCard &card){
        return out << "Knight Card";
    }

    std::ostream& operator<<(std::ostream &out, const MonopolyCard &card){
        return out << "Monopoly Card";
    }

    std::ostream& operator<<(std::ostream &out, const YearOfPlentyCard &card){
        return out << "Year of Plenty Card";
    }

    std::ostream& operator<<(std::ostream &out, const RoadBuildingCard &card){
        return out << "Road Building Card";
    }

    std::ostream& operator<<(std::ostream &out, const PromotionCard &card){
        return out << "Promotion Card";
    }

    std::ostream& operator<<(std::ostream &out, const DevelopmentCard &card){
        return out << "Development Card";
    }
}


