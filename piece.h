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
    virtual void wherePiece(Piece* boxes[8][8],bool,bool);
    void useFirsStep();
    void deleteElementFs(Coordinate);
    bool firstStep{true};
    QString imageDirection = "";
    QString pieceColor = "";
    QString initialLetter = "";
    bool backgroundColor;
};

#endif // PIECE_H
