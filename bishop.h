#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
    public:
        Bishop();
        Bishop(int,int,QString,QString,QString,bool);
        void wherePiece(Piece* casillas[8][8],bool,bool);
        void addMovement(bool&,Piece*,int,int,bool);
};

#endif // BISHOP_H
