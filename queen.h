#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include <vector>
#include <cmath>

class Queen : public Piece{

    private:
        bool firstStep{true};

    public:
        Queen();
        Queen(int, int);
        void wherePiece();
};

#endif // QUEEN_H
