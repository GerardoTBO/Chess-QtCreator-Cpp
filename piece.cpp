#include "piece.h"

Piece::Piece()
{

}

Piece::Piece(QString dir_image,QString piece_color,QString class_name,bool background_color)
{
    this->dir_image = dir_image;
    this->piece_color = piece_color;
    this->class_name = class_name;
    this->background_color = background_color;
}

void Piece::wherePiece(Piece* casillas[8][8]){

}

void Piece::useFirsStep(){
    firstStep = false;
}
