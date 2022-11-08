#include "ship.h"

BattleShip::ship::ship(char type, int size) : type(type), size(size), health(size) {
    row = col = place_method = -1;
}

void BattleShip::ship::hit() {
    this->health--;
}

bool BattleShip::ship::isDead() const {
    return this->health <= 0;
}

char BattleShip::ship::getType() const {
    return type;
}

int BattleShip::ship::getSize() const {
    return size;
}

int BattleShip::ship::getRow() const {
    return row;
}

void BattleShip::ship::setRow(int row_num) {
    ship::row = row_num;
}

int BattleShip::ship::getCol() const {
    return col;
}

void BattleShip::ship::setCol(int col_num) {
    ship::col = col_num;
}

int BattleShip::ship::getPlaceMethod() const {
    return place_method;
}

void BattleShip::ship::setPlaceMethod(int placeMethod) {
    place_method = placeMethod;
}
