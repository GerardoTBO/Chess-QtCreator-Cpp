#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include <vector>
#include <cmath>

class Rook : public Piece {
    public:
        Rook();
        Rook(int,int,QString,bool);
        void wherePiece(Piece* boxes[8][8],bool,QString,Coordinate);
        void addMovement(bool&,Piece*,int,int,bool);
        bool wherePieceThrough(Piece* boxes[8][8],Coordinate king,Coordinate piece);
};

#endif // ROOK_H
