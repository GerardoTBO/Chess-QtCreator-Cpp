#include "king.h"

King::King()
{

}

King::King(int x, int y, QString pieceColor, bool backgroundColor) : Piece(pieceColor,"K",backgroundColor){
    actualPosition.intX = x;
    actualPosition.intY = y;
    this->imageDirection = "://pieces/"+pieceColor+"-king.png";
}

void King::wherePiece(Piece* boxes[8][8],bool jakeCheck,QString lastMove,Coordinate king) {
    possibleMovements.clear();
    qDebug() << "Los elementos disponibles del rey en la posicion ("<< actualPosition.intX << ", "<< actualPosition.intY << ") son\n";
    //    for (int x = 0; x < 8; x++) {
    //        for (int y = 0; y < 8; y++) {
    //            if(boxes[x][y]->pieceColor.compare(pieceColor)!=0 && ((abs(x-actualPosition.intX) == 1 && abs(y-actualPosition.intY) == 1)
    //                                                                       || (abs(x-actualPosition.intX) == 1 && y-actualPosition.intY == 0 )
    //                                                                       || (abs(y-actualPosition.intY) == 1 && x-actualPosition.intX == 0 ))) {
    //                temporalPosition.intX = x;
    //                temporalPosition.intY = y;
    //                possibleMovements.push_back(temporalPosition);
    //            }
    //        }
    //    }
    for(int i=0;i<8 && (verifiedPosition(actualPosition.intX+1,actualPosition.intY) && boxes[actualPosition.intX+1][actualPosition.intY]->pieceColor.compare(pieceColor)!=0) ;i++){
        if(!verifiedCheck(actualPosition.intX+1,actualPosition.intY,i,boxes) && i==7){
            temporalPosition.intX = actualPosition.intX+1;
            temporalPosition.intY = actualPosition.intY;
            possibleMovements.push_back(temporalPosition);
        }
        if(verifiedCheck(actualPosition.intX+1,actualPosition.intY,i,boxes)){
            break;
        }
    }

    for(int i=0;i<8 && (verifiedPosition(actualPosition.intX+1,actualPosition.intY+1) && boxes[actualPosition.intX+1][actualPosition.intY+1]->pieceColor.compare(pieceColor)!=0) ;i++){
        if(!verifiedCheck(actualPosition.intX+1,actualPosition.intY+1,i,boxes) && i==7){
            temporalPosition.intX = actualPosition.intX+1;
            temporalPosition.intY = actualPosition.intY+1;
            possibleMovements.push_back(temporalPosition);
        }
        if(verifiedCheck(actualPosition.intX+1,actualPosition.intY+1,i,boxes)){
            break;
        }
    }

    for(int i=0;i<8 && (verifiedPosition(actualPosition.intX,actualPosition.intY+1) && boxes[actualPosition.intX][actualPosition.intY+1]->pieceColor.compare(pieceColor)!=0) ;i++){
        if(!verifiedCheck(actualPosition.intX,actualPosition.intY+1,i,boxes) && i==7){
            temporalPosition.intX = actualPosition.intX;
            temporalPosition.intY = actualPosition.intY+1;
            possibleMovements.push_back(temporalPosition);
        }
        if(verifiedCheck(actualPosition.intX,actualPosition.intY+1,i,boxes)){
            break;
        }
    }


    for(int i=0;i<8 && (verifiedPosition(actualPosition.intX-1,actualPosition.intY+1) && boxes[actualPosition.intX-1][actualPosition.intY+1]->pieceColor.compare(pieceColor)!=0) ;i++){
        if(!verifiedCheck(actualPosition.intX-1,actualPosition.intY+1,i,boxes) && i==7){
            temporalPosition.intX = actualPosition.intX-1;
            temporalPosition.intY = actualPosition.intY+1;
            possibleMovements.push_back(temporalPosition);
        }
        if(verifiedCheck(actualPosition.intX-1,actualPosition.intY+1,i,boxes)){
            break;
        }
    }
    for(int i=0;i<8 && (verifiedPosition(actualPosition.intX-1,actualPosition.intY) && boxes[actualPosition.intX-1][actualPosition.intY]->pieceColor.compare(pieceColor)!=0) ;i++){
        if(!verifiedCheck(actualPosition.intX-1,actualPosition.intY,i,boxes) && i==7){
            temporalPosition.intX = actualPosition.intX-1;
            temporalPosition.intY = actualPosition.intY;
            possibleMovements.push_back(temporalPosition);
        }
        if(verifiedCheck(actualPosition.intX-1,actualPosition.intY,i,boxes)){
            break;
        }
    }
    for(int i=0;i<8 && (verifiedPosition(actualPosition.intX-1,actualPosition.intY-1) && boxes[actualPosition.intX-1][actualPosition.intY-1]->pieceColor.compare(pieceColor)!=0) ;i++){
        if(!verifiedCheck(actualPosition.intX-1,actualPosition.intY-1,i,boxes) && i==7){
            temporalPosition.intX = actualPosition.intX-1;
            temporalPosition.intY = actualPosition.intY-1;
            possibleMovements.push_back(temporalPosition);
        }
        if(verifiedCheck(actualPosition.intX-1,actualPosition.intY-1,i,boxes)){
            break;
        }
    }
    for(int i=0;i<8 && (verifiedPosition(actualPosition.intX,actualPosition.intY-1) && boxes[actualPosition.intX][actualPosition.intY-1]->pieceColor.compare(pieceColor)!=0) ;i++){
        if(!verifiedCheck(actualPosition.intX,actualPosition.intY-1,i,boxes) && i==7){
            temporalPosition.intX = actualPosition.intX;
            temporalPosition.intY = actualPosition.intY-1;
            possibleMovements.push_back(temporalPosition);
        }
        if(verifiedCheck(actualPosition.intX,actualPosition.intY-1,i,boxes)){
            break;
        }
    }
    for(int i=0;i<8 && (verifiedPosition(actualPosition.intX+1,actualPosition.intY-1) && boxes[actualPosition.intX+1][actualPosition.intY-1]->pieceColor.compare(pieceColor)!=0) ;i++){
        if(!verifiedCheck(actualPosition.intX+1,actualPosition.intY-1,i,boxes) && i==7){
            temporalPosition.intX = actualPosition.intX+1;
            temporalPosition.intY = actualPosition.intY-1;
            possibleMovements.push_back(temporalPosition);
        }
        if(verifiedCheck(actualPosition.intX+1,actualPosition.intY-1,i,boxes)){
            break;
        }
    }

    //Sentido del reloj
    //direcciones permitidas  este, oeste
    bool directions[2]={true,true};
    //Calculando enroque oeste
    for(int y=actualPosition.intY-1; y>=0 && directions[1] && firstStep && !jakeCheck; y--){
        if(boxes[actualPosition.intX][y]->initialLetter.compare("R")==0 && boxes[actualPosition.intX][y]->firstStep){
            temporalPosition.intX = actualPosition.intX;
            temporalPosition.intY = y;
            possibleMovements.push_back(temporalPosition);
        }
        if(boxes[actualPosition.intX][y]->initialLetter.compare("")!=0){
            directions[1]=false;
        }
    }
    //Calculando enroque este
    for(int y=actualPosition.intY+1; y<=7 && directions[0] && firstStep && !jakeCheck; y++){
        if(boxes[actualPosition.intX][y]->initialLetter.compare("R")==0 && boxes[actualPosition.intX][y]->firstStep){
            temporalPosition.intX = actualPosition.intX;
            temporalPosition.intY = y;
            possibleMovements.push_back(temporalPosition);
        }
        if(boxes[actualPosition.intX][y]->initialLetter.compare("")!=0){
            directions[0]=false;
        }
    }
}

bool King::verifiedCheck(int xN,int yN, int direction,Piece* boxes[8][8]){
    //Comprobacion de knights
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(boxes[x][y]->initialLetter.compare("N")==0 && boxes[x][y]->pieceColor.compare(pieceColor)!=0 && (((x-2 == xN || x+2 == xN) && (y-1 == yN || y+1 == yN))
                                                                                                                || ((y-2 == yN || y+2 == yN) && (x-1 == xN || x+1 == xN)))) {
                return true;
            }
        }
    }

    //Comprobacion de pawns
    if(pieceColor.compare("white")==0){
        if(verifiedPosition(xN+1,yN-1) && boxes[xN+1][yN-1]->initialLetter.compare("P")==0 && boxes[xN+1][yN-1]->pieceColor.compare("black")==0){
            return true;
        }
        else if(verifiedPosition(xN+1,yN+1) && boxes[xN+1][yN+1]->initialLetter.compare("P")==0 && boxes[xN+1][yN+1]->pieceColor.compare("black")==0){
            return true;
        }
    }
    else if(pieceColor.compare("black")==0){
        if(verifiedPosition(xN-1,yN-1) && boxes[xN-1][yN-1]->initialLetter.compare("P")==0 && boxes[xN-1][yN-1]->pieceColor.compare("white")==0){
            return true;
        }
        else if(verifiedPosition(xN-1,yN+1) && boxes[xN-1][yN+1]->initialLetter.compare("P")==0 && boxes[xN-1][yN+1]->pieceColor.compare("white")==0){
            return true;
        }
    }

    //Comprobaciond e kings
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(boxes[x][y]->initialLetter.compare("K")==0 && boxes[x][y]->pieceColor.compare(pieceColor)!=0 && ((abs(x-xN) == 1 && abs(y-yN) == 1)
                                                                  || (abs(x-xN) == 1 && y-yN == 0 )
                                                                  || (abs(y-yN) == 1 && x-xN == 0 ))) {
                return true;
            }
        }
    }

    //Comprobacion de Rooks Bishops y Queen enemigos
    if(direction==0){
        for(int x=xN+1; verifiedPosition(x,yN); x++){
            QString colorNextPiece = boxes[x][yN]->pieceColor;
            QString initialNextPiece = boxes[x][yN]->initialLetter;
            if(pieceColor.compare(colorNextPiece)==0 || initialNextPiece.compare("N")==0 || initialNextPiece.compare("P")==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(pieceColor.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("R")==0 || initialNextPiece.compare("Q")==0) ){
                return true;
            }
        }
    }
    else if(direction==1){
        for(int x=xN+1, y=yN+1; verifiedPosition(x,y); x++, y++){
            QString colorNextPiece = boxes[x][y]->pieceColor;
            QString initialNextPiece = boxes[x][y]->initialLetter;
            if(pieceColor.compare(colorNextPiece)==0 || initialNextPiece.compare("N")==0 || initialNextPiece.compare("P")==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(pieceColor.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("B")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==2){
        for(int y=yN+1; verifiedPosition(xN,y); y++){
            QString colorNextPiece = boxes[xN][y]->pieceColor;
            QString initialNextPiece = boxes[xN][y]->initialLetter;
            if(pieceColor.compare(colorNextPiece)==0 || initialNextPiece.compare("N")==0 || initialNextPiece.compare("P")==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(pieceColor.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("R")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==3){
        for(int x=xN-1, y=yN+1; verifiedPosition(x,y); x--, y++){
            QString colorNextPiece = boxes[x][y]->pieceColor;
            QString initialNextPiece = boxes[x][y]->initialLetter;
            if(pieceColor.compare(colorNextPiece)==0 || initialNextPiece.compare("N")==0 || initialNextPiece.compare("P")==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(pieceColor.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("B")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==4){
        for(int x=xN-1; verifiedPosition(x,yN); x--){
            QString colorNextPiece = boxes[x][yN]->pieceColor;
            QString initialNextPiece = boxes[x][yN]->initialLetter;
            if(pieceColor.compare(colorNextPiece)==0 || initialNextPiece.compare("N")==0 || initialNextPiece.compare("P")==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(pieceColor.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("R")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==5){
        for(int x=xN-1, y=yN-1; verifiedPosition(x,y); x--, y--){
            QString colorNextPiece = boxes[x][y]->pieceColor;
            QString initialNextPiece = boxes[x][y]->initialLetter;
            if(pieceColor.compare(colorNextPiece)==0 || initialNextPiece.compare("N")==0 || initialNextPiece.compare("P")==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(pieceColor.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("B")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==6){
        for(int y=yN-1; verifiedPosition(xN,y); y--){
            QString colorNextPiece = boxes[xN][y]->pieceColor;
            QString initialNextPiece = boxes[xN][y]->initialLetter;
            if(pieceColor.compare(colorNextPiece)==0 || initialNextPiece.compare("N")==0 || initialNextPiece.compare("P")==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(pieceColor.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("R")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==7){
        for(int x=xN+1, y=yN-1; verifiedPosition(x,y); x++, y--){
            QString colorNextPiece = boxes[x][y]->pieceColor;
            QString initialNextPiece = boxes[x][y]->initialLetter;
            if(pieceColor.compare(colorNextPiece)==0 || initialNextPiece.compare("N")==0 || initialNextPiece.compare("P")==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(pieceColor.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("B")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    return false;
}
