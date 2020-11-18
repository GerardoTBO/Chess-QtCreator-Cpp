#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {

    private:
        bool firstStep{true};
        bool secondStep{false};
        bool estaLleno{false};


    public:
        Pawn();
        Pawn(int, int);
        void wherePiece();
};

#endif // PAWN_H
