#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {

    private:
        bool firstStep{true};

    public:
        Bishop();
        Bishop(int, int);
        void wherePiece();
};

#endif // BISHOP_H
