#include "piece.h"

Piece::Piece()
{

}

Piece::Piece(QString pieceColor,QString initialLetter,bool backgroundColor)
{
    this->pieceColor = pieceColor;
    this->initialLetter = initialLetter;
    this->backgroundColor = backgroundColor;
}

void Piece::wherePiece(Piece* boxes[8][8],bool firstIteracion,bool jakeCheck){

}

void Piece::useFirsStep(){
    firstStep = false;
}

void Piece::deleteElementFs(Coordinate){

}
