#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include <vector>
#include <cmath>

class Rook : public Piece {
    public:
        Rook();
        Rook(int,int,QString,bool);
        void wherePiece(Piece* boxes[8][8],bool,bool);
        void addMovement(bool&,Piece*,int,int,bool);
};

#endif // ROOK_H
