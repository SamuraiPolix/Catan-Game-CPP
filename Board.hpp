#include <vector>
#include <string>

using std::vector, std::string;

namespace ariel {
    class Board
    {
    private:
        vector<vector<string>> board;
        vector<vector<int>> boardNum;

    public:
        Board();
        
        void placeSettlement(vector<string> places, vector<int> placesNum, string name);
        void placeRoad(vector<string> places, vector<int> placesNum, string name);
        void printBoard();
    };
}