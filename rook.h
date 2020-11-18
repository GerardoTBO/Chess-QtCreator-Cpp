#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include <vector>
#include <cmath>

class Rook : public Piece {

    private:
        bool firstStep{true};

    public:
        Rook();
        Rook(int, int);
        void wherePiece();

};

#endif // ROOK_H
