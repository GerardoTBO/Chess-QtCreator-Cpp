#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include <vector>
#include <string>
#include <cmath>

class Knight : public Piece{
    public:
        Knight();
        Knight(int,int,QString,bool);
        void wherePiece(Piece* boxes[8][8],bool,QString,Coordinate);
};

#endif // KNIGHT_H
