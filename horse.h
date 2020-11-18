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
        Horse(int,int,QString,QString,QString,bool);
        void wherePiece();
};

#endif // HORSE_H
