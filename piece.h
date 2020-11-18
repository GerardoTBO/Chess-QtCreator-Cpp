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
    Piece(QString,QString,QString,bool);
    QString dir_image = "";
    QString piece_color = "";
    QString class_name = "";
    bool background_color;
    Coordinate coor;
    std::vector<Coordinate> fs;
    virtual void wherePiece();
};

#endif // PIECE_H
