#include "pawn.h"

Pawn::Pawn()
{

}

Pawn::Pawn(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"P",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-pawn.png";
}

void Pawn::wherePiece(Piece* boxes[8][8],bool jakeCheck,QString lastMove,Coordinate king) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles del peon en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";

    if(pieceColor.compare("white")==0){
        if(verifiedPosition(actualPosition.intX+1,actualPosition.intY) && boxes[actualPosition.intX+1][actualPosition.intY]->pieceColor.compare("")==0){
            addMovement(actualPosition.intX+1,actualPosition.intY,jakeCheck);
        }
        if(verifiedPosition(actualPosition.intX+2,actualPosition.intY) && boxes[actualPosition.intX+2][actualPosition.intY]->pieceColor.compare("")==0 && possibleMovements.size()!=0 && firstStep){
            addMovement(actualPosition.intX+2,actualPosition.intY,jakeCheck);
        }
        if(verifiedPosition(actualPosition.intX+1,actualPosition.intY+1) && (boxes[actualPosition.intX+1][actualPosition.intY+1]->pieceColor.compare("black")==0 || isPassant(lastMove,boxes,actualPosition.intX+1,actualPosition.intY+1))){
            addMovement(actualPosition.intX+1,actualPosition.intY+1,jakeCheck);
        }
        if(verifiedPosition(actualPosition.intX+1,actualPosition.intY-1) && (boxes[actualPosition.intX+1][actualPosition.intY-1]->pieceColor.compare("black")==0 || isPassant(lastMove,boxes,actualPosition.intX+1,actualPosition.intY-1))){
            addMovement(actualPosition.intX+1,actualPosition.intY-1,jakeCheck);
        }
    }
    else if(pieceColor.compare("black")==0){
        if(verifiedPosition(actualPosition.intX-1,actualPosition.intY) && boxes[actualPosition.intX-1][actualPosition.intY]->pieceColor.compare("")==0){
            addMovement(actualPosition.intX-1,actualPosition.intY,jakeCheck);
        }
        if(verifiedPosition(actualPosition.intX-2,actualPosition.intY) && boxes[actualPosition.intX-2][actualPosition.intY]->pieceColor.compare("")==0 && possibleMovements.size()!=0 && firstStep){
            addMovement(actualPosition.intX-2,actualPosition.intY,jakeCheck);
        }
        if(verifiedPosition(actualPosition.intX-1,actualPosition.intY+1) && (boxes[actualPosition.intX-1][actualPosition.intY+1]->pieceColor.compare("white")==0 || isPassant(lastMove,boxes,actualPosition.intX-1,actualPosition.intY+1))){
            addMovement(actualPosition.intX-1,actualPosition.intY+1,jakeCheck);
        }
        if(verifiedPosition(actualPosition.intX-1,actualPosition.intY-1) && (boxes[actualPosition.intX-1][actualPosition.intY-1]->pieceColor.compare("white")==0 || isPassant(lastMove,boxes,actualPosition.intX-1,actualPosition.intY-1))){
            addMovement(actualPosition.intX-1,actualPosition.intY-1,jakeCheck);
        }
    }
    //    std::for_each(possibleMovements.begin(), possibleMovements.end(), [](Coordinate i) {
    //        qDebug() << "x: " << i.intX << ", y: " << i.intY << "\n";
    //    });
}

void Pawn::addMovement(int x,int y,bool jakeCheck){
    temporalPosition.intX = x;
    temporalPosition.intY = y;
    possibleMovements.push_back(temporalPosition);
}

bool Pawn::isPassant(QString lastMove,Piece* boxes[8][8],int x,int y){
    QString lastInitial = lastMove.left(1);
    int lastO = lastMove.mid(1,2).toInt();
    int lastD = lastMove.right(2).toInt();
    if(((pieceColor.compare("white")==0 && boxes[x-1][y]->initialLetter.compare("P")==0) || (pieceColor.compare("black")==0 && boxes[x+1][y]->initialLetter.compare("P")==0)) && (actualPosition.intX==lastD/10) && abs(actualPosition.intY-lastD%10)==1 && boxes[x][y]->initialLetter.compare("")==0 && lastInitial.compare("P")==0 && abs(lastO - lastD)==20){
        return true;
    }
    else{
        return false;
    }
}
