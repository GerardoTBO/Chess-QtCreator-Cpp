#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include <vector>
#include <cmath>

class Queen : public Piece{
    public:
        Queen();
        Queen(int,int,QString,bool);
        void wherePiece(Piece* boxes[8][8],bool,QString,Coordinate);
        void addMovement(bool&,Piece*,int,int,bool);
};

#endif // QUEEN_H
