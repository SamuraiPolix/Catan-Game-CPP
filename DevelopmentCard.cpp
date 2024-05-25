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
    }

    void RoadBuildingCard::use(){

    }

    void YearOfPlentyCard::use(){

    }

    void MonopolyCard::use(){

    }

    void KnightCard::use(){

    }

    void VictoryPointCard::use(){

    }
}


