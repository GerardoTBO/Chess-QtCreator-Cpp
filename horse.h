#ifndef HORSE_H
#define HORSE_H

#include "piece.h"
#include <vector>
#include <string>
#include <cmath>

class Horse : public Piece{

    private:
        bool firstStep{true};

    public:
        Horse();
        Horse(int, int);
        void wherePiece();
};

#endif // HORSE_H
