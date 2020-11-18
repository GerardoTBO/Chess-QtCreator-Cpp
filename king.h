#ifndef KING_H
#define KING_H

#include "piece.h"
#include <cmath>

class King : public Piece {

    private:
        bool firstStep{true};

    public:
        King();
        King(int,int,QString,QString,QString,bool);
        void wherePiece();
};

#endif // KING_H
