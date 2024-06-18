#include "Types.hpp"

namespace ariel {
    std::string getResourceName(ResourceType resource){
        switch (resource) {
            case Ore: return "ORE";
            case Wheat: return "WHT";
            case Sheep: return "SHP";
            case Wood: return "WOOD";
            case Brick: return "BRCK";
            case Desert: return "DSRT";
            default: return "";
        }
    }
}
