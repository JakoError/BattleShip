#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

#include <string>
#include <vector>
#include <algorithm>
#include "board.h"
#include "ship.h"

using std::string;
using std::vector;

namespace BattleShip {
    class player {
    private:
        BattleShip::board *board;
        vector <BattleShip::ship> ships;

    public:
        int ship_num;
        string name;

        player(int row_len, int col_len, int ship_num, const vector <BattleShip::ship> &ships, string name);

        void place_ship();

        //block type mark 0 empty 1 ship 2 hit 3 empty_hit
        void show_board(bool show_ship);

        //true for ship is hit
        static bool check_ship_hit(BattleShip::ship ship);

        //true for
        bool check_ships_hit();

        void firing(BattleShip::player *opponent);
    };

    //string split
    vector <string> split(const string &s, const string &delimiter);

    bool isNumber(const string &str);

    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }
}

#endif //BATTLESHIP_PLAYER_H
