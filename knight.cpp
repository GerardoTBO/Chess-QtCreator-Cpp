#include "knight.h"

Knight::Knight()
{

}

Knight::Knight(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"N",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-knight.png";
}

void Knight::wherePiece(Piece* boxes[8][8],bool firstIteracion,bool jakeCheck) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles del caballo en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            // (coor.int_x != x && coor.int_y != y) && (x > coor.int_x - 3 && x < coor.int_x + 3) && (y > coor.int_y - 3 && y < coor.int_y + 3) && (coor.int_x != x && coor.int_y != y) && (abs(x-y) == 1 || abs(x-y) == 3)
            if(boxes[x][y]->pieceColor.compare(pieceColor)!=0 && (((x-2 == actualPosition.intX || x+2 == actualPosition.intX) && (y-1 == actualPosition.intY || y+1 == actualPosition.intY))
                    || ((y-2 == actualPosition.intY || y+2 == actualPosition.intY) && (x-1 == actualPosition.intX || x+1 == actualPosition.intX)))) {
                temporalPosition.intX = x;
                temporalPosition.intY = y;
                possibleMovements.push_back(temporalPosition);
            }
        }
    }

//    std::for_each(possibleMovements.begin(), possibleMovements.end(), [](Coordinate i) {
//        qDebug() << "x: " << i.intX << ", y: " << i.intY << "\n";
//    });
}
