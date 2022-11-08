#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "ship.h"
#include "player.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

namespace BattleShip {
    class game {
    private:
        int row_len, col_len;
        int ship_num;
        vector<BattleShip::ship> ships;

        BattleShip::player *player1;
        BattleShip::player *player2;

    public:
        explicit game(char *path) {
            player1 = player2 = nullptr;
            //读取文件
            string line;
            ifstream configfile(path);
            getline(configfile, line);
            row_len = (int) strtol(line.c_str(), nullptr, 10);
            getline(configfile, line);
            col_len = (int) strtol(line.c_str(), nullptr, 10);
            getline(configfile, line);
            ship_num = (int) strtol(line.c_str(), nullptr, 10);

            for (int i = 0; i < ship_num; ++i) {
                getline(configfile, line);
                vector<string> strs = split(line, " ");
                BattleShip::ship a_ship = BattleShip::ship(strs[0][0], (int) strtol(strs[1].c_str(), nullptr, 10));
                ships.push_back(a_ship);
            }
            configfile.close();
            //sort ship by character
            std::sort(ships.begin(), ships.end(), [](auto &&l, auto &&r) { return l.getType() < r.getType(); });
        }

        void setup() {
            while (true) {
                string input;
                cout << "Player 1 please enter your name: ";
                std::getline(cin, input);
                if (!input.empty() && input.length() <= 20) {
                    player1 = new BattleShip::player(row_len, col_len, ship_num, ships, input);
                    break;
                }
            }
            player1->place_ship();

            while (true) {
                string input;
                cout << "Player 2 please enter your name: ";
                std::getline(cin, input);
                if (!input.empty() && input.length() <= 20) {
                    player2 = new BattleShip::player(row_len, col_len, ship_num, ships, input);
                    break;
                }
            }
            player2->place_ship();
        }

        void run() {
            //游戏循环
            while (true) {
                player1->firing(player2);
                if (player2->check_ships_hit()) {
                    cout << player1->name << " won the game!" << endl;
                    break;
                }
                player2->firing(player1);
                if (player1->check_ships_hit()) {
                    cout << player2->name << " won the game!" << endl;
                    break;
                }
            }
            cout << endl;
        }
    };
}

int main(int argv, char **args) {
    if (argv != 2) {
        printf("Usge: BattleShip path_of_config_file\n");
        return 1;
    }

    BattleShip::game this_game = BattleShip::game(args[1]);

    this_game.setup();
    this_game.run();

    return 0;
}
