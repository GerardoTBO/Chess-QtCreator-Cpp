#include "bishop.h"

Bishop::Bishop()
{

}

Bishop::Bishop(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"B",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-bishop.png";
}

void Bishop::wherePiece(Piece* boxes[8][8],bool jakeCheck,QString lastMove,Coordinate king) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles del alfil en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";

    //Sentido del reloj
    //direcciones permitidas  noreste, sureste, suroeste, noroeste
    bool directions[4] = {true, true, true, true};

    int kingDirection = directionKingToPiece(boxes,king,actualPosition);

    if(kingDirection%2==0 && verifiedPieceToEnemy(kingDirection,boxes,actualPosition)){
        directions[0] = false;
        directions[1] = false;
        directions[2] = false;
        directions[3] = false;
    }
    else if((kingDirection==1 || kingDirection==5) && verifiedPieceToEnemy(kingDirection,boxes,actualPosition)){
        directions[1] = false;
        directions[3] = false;
    }
    else if((kingDirection==3 || kingDirection==7) && verifiedPieceToEnemy(kingDirection,boxes,actualPosition)){
        directions[0] = false;
        directions[2] = false;
    }

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
