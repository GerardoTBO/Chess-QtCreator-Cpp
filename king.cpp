#include "king.h"

King::King()
{

}

King::King(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"K",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-king.png";
}

void King::wherePiece(Piece* boxes[8][8],bool firstIteracion,bool jakeCheck) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles del rey en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(boxes[x][y]->pieceColor.compare(pieceColor)!=0 && ((abs(x-actualPosition.intX) == 1 && abs(y-actualPosition.intY) == 1)
                                                                       || (abs(x-actualPosition.intX) == 1 && y-actualPosition.intY == 0 )
                                                                       || (abs(y-actualPosition.intY) == 1 && x-actualPosition.intX == 0 ))) {
                temporalPosition.intX = x;
                temporalPosition.intY = y;
                possibleMovements.push_back(temporalPosition);
            }
        }
    }

    //Calculando jake
    for(int x=0; x<8 && firstIteracion; x++){
        for(int y=0;y<8;y++){
            if(boxes[x][y]->initialLetter.compare("")!=0 && boxes[x][y]->pieceColor.compare(pieceColor)!=0){
                boxes[x][y]->wherePiece(boxes,false,false);
                //recorre fs de casillas[x][y] y borra las coincidencias con fs de king
                for(std::size_t i=0;i<boxes[x][y]->possibleMovements.size();i++){
                    deleteElementFs(possibleMovements[i]);
                }
            }
        }
    }

    std::for_each(possibleMovements.begin(), possibleMovements.end(), [](Coordinate i) {
        qDebug() << "x: " << i.intX << ", y: " << i.intY << "\n";
    });
}
