#include "rook.h"

Rook::Rook()
{

}

Rook::Rook(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"R",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-rook.png";
}

void Rook::wherePiece(Piece* boxes[8][8],bool jakeCheck,QString lastMove,Coordinate king) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles de la torre en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";

    //Sentido del reloj
    //direcciones permitidas norte, este, sur, oeste
    bool directions[4] = {true, true, true, true};

    int kingDirection = directionKingToPiece(boxes,king,actualPosition);

    if((kingDirection==0 || kingDirection==4) && verifiedPieceToEnemy(kingDirection,boxes,actualPosition)){
        directions[1] = false;
        directions[3] = false;
    }
    else if((kingDirection==2 || kingDirection==6) && verifiedPieceToEnemy(kingDirection,boxes,actualPosition)){
        directions[0] = false;
        directions[2] = false;
    }
    else if(kingDirection!=-1 && kingDirection%2==1 && verifiedPieceToEnemy(kingDirection,boxes,actualPosition)){
        directions[0] = false;
        directions[1] = false;
        directions[2] = false;
        directions[3] = false;
    }

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
