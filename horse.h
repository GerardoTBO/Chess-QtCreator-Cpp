#ifndef HORSE_H
#define HORSE_H

#include "piece.h"
#include <vector>
#include <string>
#include <cmath>

class Horse : public Piece{
    public:
        Horse();
        Horse(int,int,QString,QString,QString,bool);
        void wherePiece(Piece* casillas[8][8]);
};

#endif // HORSE_H
