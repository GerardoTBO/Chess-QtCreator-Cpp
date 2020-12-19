#include "bishop.h"

Bishop::Bishop()
{

}

Bishop::Bishop(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"B",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-bishop.png";
}

void Bishop::wherePiece(Piece* boxes[8][8],bool firstIteracion,bool jakeCheck) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles del alfil en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";
//    for (int x = 0; x < 8; x++) {
//        for (int y = 0; y < 8; y++) {
//            if( abs(x-coor.int_x) == abs(y-coor.int_y) && (coor.int_x != x && coor.int_y != y) ) {
//                pos.int_x = x;
//                pos.int_y = y;
//                fs.push_back(pos);
//            }
//        }
//    }

    //Sentido del reloj
    //direcciones permitidas  noreste, sureste, suroeste, noroeste
    bool directions[4] = {true, true, true, true};

    //Movimiemtos hacia noreste
    for(int x=actualPosition.intX+1, y=actualPosition.intY+1; x<8 && y<8 && directions[0]; x++, y++){
        addMovement(directions[0],boxes[x][y],x,y,jakeCheck);
    }

    //Movimiemtos hacia sureste
    for(int x=actualPosition.intX-1, y=actualPosition.intY+1; x>=0 && y<8 && directions[1]; x--, y++){
        addMovement(directions[1],boxes[x][y],x,y,jakeCheck);
    }

    //Movimiemtos hacia suroeste
    for(int x=actualPosition.intX-1, y=actualPosition.intY-1; x>=0 && y>=0 && directions[2]; x--, y--){
        addMovement(directions[2],boxes[x][y],x,y,jakeCheck);
    }

    //Movimiemtos hacia noroeste
    for(int x=actualPosition.intX+1, y=actualPosition.intY-1; x<8 && y>=0 && directions[3]; x++, y--){
        addMovement(directions[3],boxes[x][y],x,y,jakeCheck);
    }

//    std::for_each(possibleMovements.begin(), possibleMovements.end(), [](Coordinate i) {
//        qDebug() << "x: " << i.intX << ", y: " << i.intY << "\n";
//    });
}

void Bishop::addMovement(bool& d,Piece* p,int x,int y,bool jakeCheck){
    //Si es una pieza jugable del mismo color
    if(p->pieceColor.compare(pieceColor)==0){
        d=false;
    }
    //Si es una pieza jugable de diferente color
    else if(p->pieceColor.compare("")!=0){
        if(jakeCheck && p->initialLetter.compare("K")==0){
            qDebug() << "El rey esta en jake\n";
        }
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
