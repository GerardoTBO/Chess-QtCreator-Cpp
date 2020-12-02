#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include <vector>
#include <cmath>

class Rook : public Piece {
    public:
        Rook();
        Rook(int,int,QString,QString,QString,bool);
        void wherePiece(Piece* casillas[8][8]);
        void addMovement(bool&,Piece*,int,int);
};

#endif // ROOK_H
