#include "rook.h"

Rook::Rook()
{

}

Rook::Rook(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"R",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-rook.png";
}

void Rook::wherePiece(Piece* boxes[8][8],bool firstIteracion,bool jakeCheck) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles de la torre en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";
//    for (int x = 0; x < 8; x++) {
//        for (int y = 0; y < 8; y++) {
//            if( (x != coor.int_x && y == coor.int_y) || (y != coor.int_y && x == coor.int_x) ) {
//                pos.int_x = x;
//                pos.int_y = y;
//                fs.push_back(pos);
//            }
//        }
//    }

    //Sentido del reloj
    //direcciones permitidas norte, este, sur, oeste
    bool directions[4] = {true, true, true, true};

    //Movimiemtos hacia el norte
    for(int x=actualPosition.intX+1; x<8 && directions[0]; x++){
        addMovement(directions[0],boxes[x][actualPosition.intY],x,actualPosition.intY,jakeCheck);
    }

    //Movimiemtos hacia la este
    for(int y=actualPosition.intY+1; y<8 && directions[1]; y++){
        addMovement(directions[1],boxes[actualPosition.intX][y],actualPosition.intX,y,jakeCheck);
    }

    //Movimiemtos hacia sur
    for(int x=actualPosition.intX-1; x>=0 && directions[2]; x--){
        addMovement(directions[2],boxes[x][actualPosition.intY],x,actualPosition.intY,jakeCheck);
    }

    //Movimiemtos hacia el oeste
    for(int y=actualPosition.intY-1; y>=0 && directions[3]; y--){
        addMovement(directions[3],boxes[actualPosition.intX][y],actualPosition.intX,y,jakeCheck);
    }

    std::for_each(possibleMovements.begin(), possibleMovements.end(), [](Coordinate i) {
        qDebug() << "x: " << i.intX << ", y: " << i.intY << "\n";
    });
}

void Rook::addMovement(bool& d,Piece* p,int x,int y,bool jakeCheck){
    //Si es una pieza jugable del mismo color
    if(p->pieceColor.compare(pieceColor)==0){
        d=false;
    }
    //Si es una pieza jugable de diferente color
    else if(p->pieceColor.compare("")!=0){
        temporalPosition.intX = x;
        temporalPosition.intY = y;
        possibleMovements.push_back(temporalPosition);
        d=false;
    }
    else{
        temporalPosition.intX = x;
        temporalPosition.intY = y;
        possibleMovements.push_back(temporalPosition);
    }
}
