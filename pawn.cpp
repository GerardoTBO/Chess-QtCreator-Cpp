#include "pawn.h"

Pawn::Pawn()
{

}

Pawn::Pawn(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"P",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-pawn.png";
}

void Pawn::wherePiece(Piece* boxes[8][8],bool firstIteracion,bool jakeCheck) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles del peon en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";

    bool norte = true;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(boxes[x][y]->pieceColor.compare("")==0 && pieceColor.compare("white")==0 && (actualPosition.intX + (1+firstStep) >= x && x > actualPosition.intX) && y == actualPosition.intY) {
                addMovement(x,y,jakeCheck);
            }
            else if(boxes[x][y]->pieceColor.compare("black")==0 && pieceColor.compare("white")==0 && ((actualPosition.intX+1==x && actualPosition.intY-1==y) || (actualPosition.intX+1==x && actualPosition.intY+1==y))){
                addMovement(x,y,jakeCheck);
            }
            else if(boxes[x][y]->pieceColor.compare("")==0 && pieceColor.compare("black")==0 && (actualPosition.intX - (1+firstStep) <= x && x < actualPosition.intX) && y == actualPosition.intY) {
                addMovement(x,y,jakeCheck);
            }
            else if(boxes[x][y]->pieceColor.compare("white")==0 && pieceColor.compare("black")==0 && ((actualPosition.intX-1==x && actualPosition.intY-1==y) || (actualPosition.intX-1==x && actualPosition.intY+1==y))){
                addMovement(x,y,jakeCheck);
            }
        }
    }
    std::for_each(possibleMovements.begin(), possibleMovements.end(), [](Coordinate i) {
        qDebug() << "x: " << i.intX << ", y: " << i.intY << "\n";
    });

}

void Pawn::addMovement(int x,int y,bool jakeCheck){
    temporalPosition.intX = x;
    temporalPosition.intY = y;
    possibleMovements.push_back(temporalPosition);
}
