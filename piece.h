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
    Coordinate pos;
    std::vector<Coordinate> fs;
    virtual void wherePiece(Piece* casillas[8][8],bool,bool);
    void useFirsStep();
    void deleteElementFs(Coordinate);

    QString dir_image = "";
    QString piece_color = "";
    QString class_name = "";
    bool background_color;
};

#endif // PIECE_H
