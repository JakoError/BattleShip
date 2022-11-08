#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "board.h"
#include "ship.h"
#include "player.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;


//block type mark 0 empty 1 ship 2 hit 3 empty_hit
BattleShip::player::player(int row_len, int col_len, int ship_num, const vector<BattleShip::ship> &ships, string name) {
    this->board = new BattleShip::board(row_len, col_len);
    this->ship_num = ship_num;
    std::copy(ships.begin(), ships.end(), std::back_inserter(this->ships));
    this->name = std::move(name);
}

// place_method 0:横放  1:竖放
void BattleShip::player::place_ship() {
    this->show_board(true);
    for (int i = 0; i < this->ship_num; i++) {
        int place_method;
        string input;
        while (true) {
            while (true) {
                cout << this->name << ", do you want to place " << this->ships[i].getType()
                     << " horizontally or vertically?"
                     << endl;
                cout << "Enter h for horizontal or v for vertical" << endl;
                cout << "Your choice: ";
                std::getline(cin, input);
                trim(input);
                if (input == "h" || input == "H") {
                    place_method = BattleShip::HORIZONTAL;
                } else if (input == "v" || input == "V") {
                    place_method = BattleShip::VERTICAL;
                } else {
                    continue;
                }
                break;
            }

            cout << this->name << ", enter the row and column you want to place " << this->ships[i].getType()
                 << ", which is " << this->ships[i].getSize() << " long, at with a space in between row and col: ";
            std::getline(cin, input);
            trim(input);
            vector<string> strs = split(input, " ");
            if (strs.size() == 2) {
                if (isNumber(strs[0]) && isNumber(strs[1])) {
                    int row, col;
                    row = (int) strtol(strs[0].c_str(), nullptr, 10);
                    col = (int) strtol(strs[1].c_str(), nullptr, 10);
                    if (this->board->place_ship(row, col, place_method, this->ships[i].getSize(),
                                                this->ships[i].getType(), i)) {
                        this->ships[i].setRow(row);
                        this->ships[i].setCol(col);
                        this->ships[i].setPlaceMethod(place_method);
                        this->show_board(true);
                        break;
                    }
                }
            }
        }
    }
}

void BattleShip::player::firing(BattleShip::player *opponent) {
    while (true) {

        cout << name << "'s Firing Board" << endl;
        opponent->show_board(false);
        cout << endl;
        cout << endl;
        cout << name << "'s Placement Board" << endl;
        this->show_board(true);

        int row, col;

        while (true) {
            string input;
            cout << name << ", where would you like to fire?" << endl;
            cout << "Enter your attack coordinate in the form row col: ";
            std::getline(cin, input);
            trim(input);
            vector<string> strs = split(input, " ");
            if (strs.size() == 2) {
                if (isNumber(strs[0]) && isNumber(strs[1])) {
                    row = (int) strtol(strs[0].c_str(), nullptr, 10);
                    col = (int) strtol(strs[1].c_str(), nullptr, 10);
                    break;
                }
            }
        }

        bool is_hit = false;
        if (opponent->board->hit(row, col, &is_hit)) {
            cout << name << "'s Firing Board" << endl;
            opponent->show_board(false);
            cout << endl;
            cout << endl;
            cout << name << "'s Placement Board" << endl;
            this->show_board(true);
            if (is_hit) {
                ship *target_ship = &opponent->ships[opponent->board->get_ship_idx(row, col)];
                target_ship->hit();

                cout << name << " hit " << opponent->name << "'s " << target_ship->getType()
                     << "!" << endl;
                if (BattleShip::player::check_ship_hit(*target_ship)) {
                    cout << name << " destroyed " << opponent->name << "'s "
                         << opponent->board->get_type(row, col) << "!" << endl;
                }
                cout << endl;
            } else {
                cout << "Missed." << endl;
                cout << endl;
            }
            break;
        }
    }
}


/**
 * show the whole board
 * @param show_ship show ship or not
 */
void BattleShip::player::show_board(bool show_ship) {
    cout << "  ";
    for (int i = 0; i < this->board->col_len; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < this->board->row_len; i++) {
        cout << i << " ";
        for (int j = 0; j < this->board->col_len; j++) {
            int status_num = this->board->get_status(i, j);
            if (status_num == 0) {
                cout << "* ";
            } else if (status_num == 1) {
                if (show_ship) {
                    cout << this->board->get_type(i, j) << " ";
                } else {
                    cout << "* ";
                }
            } else if (status_num == 2) {
                cout << "X ";
            } else if (status_num == 3) {
                cout << "O ";
            }
        }
        cout << endl;
    }
}

//true for ship is all hit
bool BattleShip::player::check_ship_hit(BattleShip::ship ship) {
    return ship.isDead();
}

//true for all ships hit
bool BattleShip::player::check_ships_hit() {
    for (auto s: this->ships) {
        if (!check_ship_hit(s))
            return false;
    }
    return true;
}

//string split
vector<string> BattleShip::split(const string &s, const string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

bool BattleShip::isNumber(const string &str) {
    for (int i = 0; i < str.length(); ++i) {
        //handle sign
        if (i == 0 && str[i] == '-') continue;
        if (isdigit(str[i]) == 0) return false;
    }
    return true;
}