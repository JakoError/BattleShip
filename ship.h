#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

namespace BattleShip {
    class ship {
    public:
        ship(char type, int size);

        void hit();

        bool isDead() const;

        char getType() const;

        int getSize() const;

        int getRow() const;

        void setRow(int row_num);

        int getCol() const;

        void setCol(int col_num);

        int getPlaceMethod() const;

        void setPlaceMethod(int placeMethod);

    private:
        int health;
        char type;
        int size;
        int row;
        int col;
        int place_method;
    };
}

#endif //BATTLESHIP_SHIP_H
