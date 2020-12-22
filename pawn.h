#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
    public:
        Pawn();
        Pawn(int,int,QString,bool);
        void wherePiece(Piece* boxes[8][8],bool,QString,Coordinate);
        void addMovement(int,int,bool);
        bool isPassant(QString,Piece* boxes[8][8],int,int);
};

#endif // PAWN_H
