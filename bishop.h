#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
    public:
        Bishop();
        Bishop(int,int,QString,bool);
        void wherePiece(Piece* boxes[8][8],bool,QString,Coordinate);
        void addMovement(bool&,Piece*,int,int,bool);
};

#endif // BISHOP_H
