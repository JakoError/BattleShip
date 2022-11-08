//
// Created by JakoError on 2022/5/11.
//

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

typedef struct ele {
    int i;//block type mark 0 empty 1 ship 2 hit 3 empty_hit
    char c;//(name) of ship
    int ship_idx;//ship's index in array
} ele;

namespace BattleShip {
//block type mark 0 empty 1 ship 2 hit 3 empty_hit
    const int EMPTY = 0;
    const int SHIP = 1;
    const int HIT = 2;
    const int EMPTY_HIT = 3;

    const int HORIZONTAL = 0;
    const int VERTICAL = 1;

    class board {
    private:
        ele **arr;

    public:
        int row_len, col_len;

        board(int row_len, int col_len);

        bool place_ship(int row, int col, int place_method, int size, char type, int ship_idx);

        bool isInRange(int row, int col) const;

        bool rowInRange(int row) const;

        bool colInRange(int col) const;

        bool hit(int row, int col, bool *is_hit);

        int get_status(int row, int col);

        char get_type(int row, int col);

        int get_ship_idx(int row, int col);
    };
}

#endif //BATTLESHIP_BOARD_H
