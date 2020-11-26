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
    Piece(QString,QString,QString,bool);
    Coordinate coor;
    std::vector<Coordinate> fs;
    virtual void wherePiece(Piece* casillas[8][8]);
    void useFirsStep();

    QString dir_image = "";
    QString piece_color = "";
    QString class_name = "";
    bool background_color;
};

#endif // PIECE_H
