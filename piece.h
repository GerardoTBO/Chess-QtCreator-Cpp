#ifndef PIECE_H
#define PIECE_H
#include <QPushButton>
#include "Coordinate.h"
#include <vector>
#include <QtDebug>

class Piece : public QPushButton
{
public:
    Piece();
    Piece(QString,QString,bool);

    Coordinate actualPosition;
    Coordinate temporalPosition;
    std::vector<Coordinate> possibleMovements;
    QString imageDirection = "";
    QString pieceColor = "";
    QString initialLetter = "";
    bool firstStep{true};
    bool backgroundColor;

    int directionKingToPiece(Piece* boxes[8][8],Coordinate,Coordinate);
    virtual void wherePiece(Piece* boxes[8][8],bool,QString,Coordinate);
    bool verifiedPieceToEnemy(int,Piece* boxes[8][8],Coordinate);

    void useFirsStep();
    void deleteElementFs(Coordinate);
    bool verifiedPosition(int,int);
};

#endif // PIECE_H
