#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
    public:
        Pawn();
        Pawn(int,int,QString,QString,QString,bool);
        void wherePiece(Piece* casillas[8][8]);
        void addMovement(int,int);
};

#endif // PAWN_H
