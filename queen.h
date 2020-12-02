#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include <vector>
#include <cmath>

class Queen : public Piece{
    public:
        Queen();
        Queen(int,int,QString,QString,QString,bool);
        void wherePiece(Piece* casillas[8][8]);
        void addMovement(bool&,Piece*,int,int);
};

#endif // QUEEN_H
