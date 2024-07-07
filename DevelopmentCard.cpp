/*
 * Email: sam.lazareanu@gmail.com
 * ID: ****6281
 * @SamuraiPolix - Samuel Lazareanu
*/

#include "DevelopmentCard.hpp"
#include <iostream>

using std::cout, std::endl, std::cin;

namespace ariel{
    DevelopmentCard* DevelopmentCardFactory::createCard(CardType type, Catan* game){
        switch (type)
        {
        case Promotion:
            throw std::invalid_argument("Promotion card by itself cannot be created, please specify the type of promotion card you want.");
            break;
        case RoadBuilding:
            return new RoadBuildingCard(type, game);
            break;
        case YearOfPlenty:
            return new YearOfPlentyCard(type, game);
            break;
        case Monopoly:
            return new MonopolyCard(type, game);
            break;
        case Knight:
            return new KnightCard(type, game);
            break;
        case VictoryPoint:
            return new VictoryPointCard(type, game);
            break;
        default:
            throw std::invalid_argument("Invalid card type.");
            break;
        }
        return NULL;
    }

    // TODO add return int to all uses - return status
    void RoadBuildingCard::use(){
        // ask player for 2 roads and add them to the player
        if (owner == nullptr){
            throw std::invalid_argument("Owner of the card is not set\n");
        }
        cout << "Player " << owner->getName() << " used a Road Building card\n";
        cout << "Please choose 2 roads to place on the board:\n";
        cout << "Choose an edge to place a road (enter 2 vertex numbers, seperated by a space!)" << endl;
        int status = -1;
        for (int i = 0; i < 2; i++){
            cout << "Road #" << i+1 << ": " << endl;
            do {
                size_t vertex1, vertex2;
                cin >> vertex1;
                while (vertex1 < 0){
                    cout << "Invalid choice" << endl;
                    cin >> vertex1;
                }
                cin >> vertex2;
                while (vertex2 < 0){
                    cout << "Invalid choice" << endl;
                    cin >> vertex2;
                }
                try {
                    status = owner->placeRoad(vertex1, vertex2, game->getBoard());
                } catch (const std::invalid_argument& e){
                    cout << e.what() << endl;
                    status = -1;
                }
                if (status == -1){
                    cout << "Please choose another" << endl;
                }
            } while (status == -1);
        }
    }

    void YearOfPlentyCard::use(){
        if (owner == nullptr){
            throw std::invalid_argument("Owner of the card is not set\n");
        }
        // ask player for 2 resources and add them to the player
        cout << "Player " << owner->getName() << " used a Year of Plenty card\n";
        cout << "Please choose 2 resources to take from the bank:\n";
        cout << "Resources: 0. Ore, 1. Wheat, 2. Sheep, 3. Wood, 4. Brick" << endl;
        cout << "Write the numbers of the resources with a space between them and press enter: ";
        int resource1, resource2;
        cin >> resource1 >> resource2;
        owner->addResource((ResourceType)resource1, 1);
        owner->addResource((ResourceType)resource2, 1);
    }

    void MonopolyCard::use(){
        // ask player for a resource type and take all of that resource from all players
        if (owner == nullptr){
            throw std::invalid_argument("Owner of the card is not set\n");
        }
        cout << "Player " << owner->getName() << " used a Monopoly card\n";
        cout << "Please choose a resource to take from all players:\n";
        cout << "Resources: 0. Ore, 1. Wheat, 2. Sheep, 3. Wood, 4. Brick" << endl;
        cout << "Write the number of the resource and press enter: ";
        int resource;
        cin >> resource;
        for (size_t i = 0; i < game->getPlayers().size(); i++){
            if (game->getPlayers()[i] != owner){
                owner->addResource((ResourceType)resource, game->getPlayers()[i]->getResourceAmount((ResourceType)resource));
                cout << "Player " << owner->getName() << " took " << game->getPlayers()[i]->getResourceAmount((ResourceType)resource) << " " << resource << " from player " << game->getPlayers()[i]->getName() << endl;
                game->getPlayers()[i]->addResource((ResourceType)resource, -game->getPlayers()[i]->getResourceAmount((ResourceType)resource));
            }
        }
    }

    void KnightCard::use(){
        // no use in assignment
        throw std::invalid_argument("Knight card cannot be used in this assignment\n");
    }

    void VictoryPointCard::use(){
        // no use in assignment
        throw std::invalid_argument("Victory Point card cannot be used in this assignment. A victory point is automatically added to the player upon buying\n");
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
        switch (card.type){
            case Promotion:
                return out << "Promotion Card";
                break;
            case RoadBuilding:
                return out << "Road Building Card";
                break;
            case YearOfPlenty:
                return out << "Year of Plenty Card";
                break;
            case Monopoly:
                return out << "Monopoly Card";
                break;
            case Knight:
                return out << "Knight Card";
                break;
            case VictoryPoint:
                return out << "Victory Point Card";
                break;
            default:
                return out << "Invalid Card";
                break;
        }
    }
}


