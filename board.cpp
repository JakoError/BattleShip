#include <vector>
#include <cstdlib>
#include "board.h"

//block type mark 0 empty 1 ship 2 hit 3 empty_hit
BattleShip::board::board(int row_len, int col_len) {
    //init matrix
    arr = (ele **) malloc(sizeof(ele *) * row_len);
    for (int i = 0; i < row_len; i++) {
        arr[i] = (ele *) malloc(sizeof(ele) * col_len);
        for (int j = 0; j < col_len; j++) {
            arr[i][j].i = BattleShip::EMPTY;
            arr[i][j].c = '0';
            arr[i][j].ship_idx = -1;
        }
    }
    this->row_len = row_len;
    this->col_len = col_len;
}

// place_method 0:横放  1:竖放
bool BattleShip::board::place_ship(int row, int col, int place_method, int size, char type, int idx) {
    //row col in range
    if (!isInRange(row, col)) {
        return false;
    }
    //size invalid
    if (size < 1) {
        return false;
    }


    if (place_method == BattleShip::HORIZONTAL) {//in one row
        // printf("%d\n",col);
        if (!colInRange(col + size - 1)) {
            return false;
        }
        for (int i = col; i < size + col; i++) {
            if (this->arr[row][i].i != BattleShip::EMPTY) {
                return false;
            }
        }

        for (int i = col; i < size + col; i++) {
            this->arr[row][i].i = BattleShip::SHIP;
            this->arr[row][i].c = type;
            this->arr[row][i].ship_idx = idx;
        }
    } else {//in one col
        // printf("%d\n",row);
        if (!rowInRange(row + size - 1)) {
            return false;
        }
        for (int i = row; i < size + row; i++) {
            if (this->arr[i][col].i != BattleShip::EMPTY) {
                return false;
            }
        }
        for (int i = row; i < size + row; i++) {
            this->arr[i][col].i = BattleShip::SHIP;
            this->arr[i][col].c = type;
            this->arr[i][col].ship_idx = idx;
        }
    }
    return true;
}

/***
 * block type mark 0 empty 1 ship 2 hit 3 empty_hit
 * @param row hit row
 * @param col hit col
 * @param is_hit call back to know whether it is hit
 * @return hit is valid
 */
bool BattleShip::board::hit(int row, int col, bool *is_hit) {
    //in range || valid hit
    if (!isInRange(row, col) || this->arr[row][col].i == BattleShip::HIT ||
        this->arr[row][col].i == BattleShip::EMPTY_HIT) {
        *is_hit = false;
        return false;
    }

    if (this->arr[row][col].i == BattleShip::SHIP) {
        //ship to hit
        this->arr[row][col].i = BattleShip::HIT;
        *is_hit = true;
    } else if (this->arr[row][col].i == BattleShip::EMPTY) {
        //empty to empty_hit
        this->arr[row][col].i = BattleShip::EMPTY_HIT;
        *is_hit = false;
    }
    return true;
}

int BattleShip::board::get_status(int row, int col) {
    return this->arr[row][col].i;
}

char BattleShip::board::get_type(int row, int col) {
    return arr[row][col].c;
}

int BattleShip::board::get_ship_idx(int row, int col) {
    return arr[row][col].ship_idx;
}

bool BattleShip::board::isInRange(int row, int col) const {
    return rowInRange(row) && colInRange(col);
}

bool BattleShip::board::rowInRange(int row) const {
    return row >= 0 && row < this->row_len;
}

bool BattleShip::board::colInRange(int col) const {
    return col >= 0 && col < this->col_len;
}
