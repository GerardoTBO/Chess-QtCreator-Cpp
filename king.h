#ifndef KING_H
#define KING_H

#include "piece.h"
#include <cmath>

class King : public Piece {
    public:
        King();
        King(int,int,QString,QString,QString,bool);
        void wherePiece(Piece* casillas[8][8],bool,bool);
};

#endif // KING_H
