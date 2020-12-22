#ifndef BUILDERBOARD_H
#define BUILDERBOARD_H
#include "builderpieces.h"
#include "piece.h"



class BuilderBoard
{
public:
    BuilderPieces* builderPieces;
    BuilderBoard(BuilderPieces*);
    void assingPieces(Piece* boxes[8][8],QString);
    void resetBoard(Piece* boxes[8][8]);
    void testBoard(Piece* boxes[8][8]);
};

#endif // BUILDERBOARD_H
