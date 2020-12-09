#ifndef PIECE_H
#define PIECE_H
#include <QPushButton>
#include "Coordinate.h"
#include <vector>
#include <QtDebug>

class Piece : public QPushButton
{
protected:
    bool firstStep{true};

public:
    Piece();
    Piece(QString,QString,bool);
    Coordinate actualPosition;
    Coordinate temporalPosition;
    std::vector<Coordinate> possibleMovements;
    virtual void wherePiece(Piece* boxes[8][8],bool,bool);
    void useFirsStep();
    void deleteElementFs(Coordinate);

    QString imageDirection = "";
    QString pieceColor = "";
    QString initialLetter = "";
    bool backgroundColor;
};

#endif // PIECE_H
