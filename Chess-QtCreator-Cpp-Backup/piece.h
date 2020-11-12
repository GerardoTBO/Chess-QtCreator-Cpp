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
    QString dir_image = "";
    QString piece_color = "";
    QString class_name = "";
    Coordinate coor;
    std::vector<Coordinate> fs;
    virtual void wherePiece();
};

#endif // PIECE_H
