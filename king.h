#ifndef KING_H
#define KING_H

#include "piece.h"
#include <cmath>

class King : public Piece {
    public:
        King();
        King(int,int,QString,bool);
        void wherePiece(Piece* boxes[8][8],bool,QString,Coordinate);
        bool verifiedCheck(int,int,int,Piece* boxes[8][8]);
        bool verifiedCheckKing(int,int,Piece* boxes[8][8]);
};

#endif // KING_H
