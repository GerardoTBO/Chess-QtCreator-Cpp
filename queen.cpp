#include "queen.h"

Queen::Queen()
{

}

Queen::Queen(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"Q",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-queen.png";
}

void Queen::wherePiece(Piece* boxes[8][8],bool firstIteracion,bool jakeCheck) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles de la reina en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";
//    for (int x = 0; x < 8; x++) {
//        for (int y = 0; y < 8; y++) {
//            if( (((x < coor.int_x || x > coor.int_x) && y == coor.int_y)
//                 || ((y < coor.int_y || y > coor.int_y) && x == coor.int_x))
//                    || (abs(x-coor.int_x) == abs(y-coor.int_y)
//                        && (coor.int_x != x && coor.int_y != y)) ) {
//                pos.int_x = x;
//                pos.int_y = y;
//                fs.push_back(pos);
//            }
//        }
//    }

    //Sentido del reloj
    //direcciones permitidas norte, noreste, este, sureste, sur, suroeste, oeste, noroeste
    bool directions[8] = {true, true, true, true, true, true, true, true};

    //Movimiemtos hacia el norte
    for(int x=actualPosition.intX+1; x<8 && directions[0]; x++){
        addMovement(directions[0],boxes[x][actualPosition.intY],x,actualPosition.intY,jakeCheck);
    }

    //Movimiemtos hacia noreste
    for(int x=actualPosition.intX+1, y=actualPosition.intY+1; x<8 && y<8 && directions[1]; x++, y++){
        addMovement(directions[1],boxes[x][y],x,y,jakeCheck);
    }

    //Movimiemtos hacia al este
    for(int y=actualPosition.intY+1; y<8 && directions[2]; y++){
        addMovement(directions[2],boxes[actualPosition.intX][y],actualPosition.intX,y,jakeCheck);
    }

    //Movimiemtos hacia sureste
    for(int x=actualPosition.intX-1, y=actualPosition.intY+1; x>=0 && y<8 && directions[3]; x--, y++){
        addMovement(directions[3],boxes[x][y],x,y,jakeCheck);
    }

    //Movimiemtos hacia el sur
    for(int x=actualPosition.intX-1; x>=0 && directions[4]; x--){
        addMovement(directions[4],boxes[x][actualPosition.intY],x,actualPosition.intY,jakeCheck);
    }

    //Movimiemtos hacia suroeste
    for(int x=actualPosition.intX-1, y=actualPosition.intY-1; x>=0 && y>=0 && directions[5]; x--, y--){
        addMovement(directions[5],boxes[x][y],x,y,jakeCheck);
    }

    //Movimiemtos hacia al oeste
    for(int y=actualPosition.intY-1; y>=0 && directions[6]; y--){
        addMovement(directions[6],boxes[actualPosition.intX][y],actualPosition.intX,y,jakeCheck);
    }

    //Movimiemtos hacia noroeste
    for(int x=actualPosition.intX+1, y=actualPosition.intY-1; x<8 && y>=0 && directions[7]; x++, y--){
        addMovement(directions[7],boxes[x][y],x,y,jakeCheck);
    }

//    std::for_each(possibleMovements.begin(), possibleMovements.end(), [](Coordinate i) {
//        qDebug() << "x: " << i.intX << ", y: " << i.intY << "\n";
//    });
}

void Queen::addMovement(bool& d,Piece* p,int x,int y,bool jakeCheck){
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
