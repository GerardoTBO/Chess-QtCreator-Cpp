#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
    public:
        Pawn();
        Pawn(int,int,QString,QString,QString,bool);
        void wherePiece(Piece* casillas[8][8],bool,bool);
        void addMovement(int,int,bool);
};

#endif // PAWN_H
