#include "piece.h"

Piece::Piece()
{

}

Piece::Piece(QString pieceColor,QString initialLetter,bool backgroundColor)
{
    this->pieceColor = pieceColor;
    this->initialLetter = initialLetter;
    this->backgroundColor = backgroundColor;
}

void Piece::wherePiece(Piece* boxes[8][8],bool jakeCheck,QString lastMove,Coordinate king){

}

void Piece::useFirsStep(){
    firstStep = false;
}

void Piece::deleteElementFs(Coordinate){

}

bool Piece::verifiedPosition(int x,int y){
    if(x<8 && x>=0 && y<8 && y>=0){
        return true;
    }
    else{
        return false;
    }
}
int Piece::directionKingToPiece(Piece* boxes[8][8],Coordinate king,Coordinate piece){
    //Sentido del reloj
    //direcciones permitidas norte, noreste, este, sureste, sur, suroeste, oeste, noroeste
    bool directions[8] = {true, true, true, true, true, true, true, true};

    //Comprobacion hacia el norte
    for(int x=king.intX+1; verifiedPosition(x,king.intY) && directions[0]; x++){
        if(x==piece.intX && king.intY==piece.intY){
            return 0;
        }
        else if(boxes[x][king.intY]->initialLetter.compare("")!=0){
            directions[0] = false;
        }
    }

    //Comprobacion hacia noreste
    for(int x=king.intX+1, y=king.intY+1; verifiedPosition(x,y) && directions[1]; x++, y++){
        if(x==piece.intX && y==piece.intY){
            return 1;
        }
        else if(boxes[x][y]->initialLetter.compare("")!=0){
            directions[1] = false;
        }
    }

    //Comprobacion hacia al este
    for(int y=king.intY+1; verifiedPosition(king.intX,y) && directions[2]; y++){
        if(king.intX==piece.intX && y==piece.intY){
            return 2;
        }
        else if(boxes[king.intX][y]->initialLetter.compare("")!=0){
            directions[2] = false;
        }
    }

    //Comprobacion hacia sureste
    for(int x=king.intX-1, y=king.intY+1; verifiedPosition(x,y) && directions[3]; x--, y++){
        if(x==piece.intX && y==piece.intY){
            return 3;
        }
        else if(boxes[x][y]->initialLetter.compare("")!=0){
            directions[3] = false;
        }
    }

    //Comprobacion hacia el sur
    for(int x=king.intX-1; verifiedPosition(x,king.intY) && directions[4]; x--){
        if(x==piece.intX && king.intY==piece.intY){
            return 4;
        }
        else if(boxes[x][king.intY]->initialLetter.compare("")!=0){
            directions[4] = false;
        }
    }

    //Comprobacion hacia suroeste
    for(int x=king.intX-1, y=king.intY-1; verifiedPosition(x,y) && directions[5]; x--, y--){
        if(x==piece.intX && y==piece.intY){
            return 5;
        }
        else if(boxes[x][y]->initialLetter.compare("")!=0){
            directions[5] = false;
        }
    }

    //Comprobacion hacia al oeste
    for(int y=king.intY-1; verifiedPosition(king.intX,y) && directions[6]; y--){
        if(king.intX==piece.intX && y==piece.intY){
            return 6;
        }
        else if(boxes[king.intX][y]->initialLetter.compare("")!=0){
            directions[6] = false;
        }
    }

    //Comprobacion hacia noroeste
    for(int x=king.intX+1, y=king.intY-1; verifiedPosition(x,y) && directions[7]; x++, y--){
        if(x==piece.intX && y==piece.intY){
            return 7;
        }
        else if(boxes[x][y]->initialLetter.compare("")!=0){
            directions[7] = false;
        }
    }
    return -1;
}

bool Piece::verifiedPieceToEnemy(int direction,Piece* boxes[8][8],Coordinate piece){
    if(direction==0){
        for(int x=piece.intX+1; verifiedPosition(x,piece.intY); x++){
            QString colorPiece = boxes[piece.intX][piece.intY]->pieceColor;
            QString colorNextPiece = boxes[x][piece.intY]->pieceColor;
            QString initialNextPiece = boxes[x][piece.intY]->initialLetter;
            //La siguiente pieza esta vacia
            if(colorNextPiece.compare("")==0){
                continue;
            }
            else if(colorPiece.compare(colorNextPiece)==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(colorPiece.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("R")==0 || initialNextPiece.compare("Q")==0) ){
                return true;
            }
        }
    }
    else if(direction==1){
        for(int x=piece.intX+1, y=piece.intY+1; verifiedPosition(x,y); x++, y++){
            QString colorPiece = boxes[piece.intX][piece.intY]->pieceColor;
            QString colorNextPiece = boxes[x][y]->pieceColor;
            QString initialNextPiece = boxes[x][y]->initialLetter;
            //La siguiente pieza esta vacia
            if(colorNextPiece.compare("")==0){
                continue;
            }
            else if(colorPiece.compare(colorNextPiece)==0){
                return false;
            }
            //La siguiente pieza es enemiga
            else if(colorPiece.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("B")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==2){
        for(int y=piece.intY+1; verifiedPosition(piece.intX,y); y++){
            QString colorPiece = boxes[piece.intX][piece.intY]->pieceColor;
            QString colorNextPiece = boxes[piece.intX][y]->pieceColor;
            QString initialNextPiece = boxes[piece.intX][y]->initialLetter;
            //La siguiente pieza esta vacia
            if(colorNextPiece.compare("")==0){
                continue;
            }
            //La siguiente pieza es enemiga
            else if(colorPiece.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("R")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==3){
        for(int x=piece.intX-1, y=piece.intY+1; verifiedPosition(x,y); x--, y++){
            QString colorPiece = boxes[piece.intX][piece.intY]->pieceColor;
            QString colorNextPiece = boxes[x][y]->pieceColor;
            QString initialNextPiece = boxes[x][y]->initialLetter;
            //La siguiente pieza esta vacia
            if(colorNextPiece.compare("")==0){
                continue;
            }
            //La siguiente pieza es enemiga
            else if(colorPiece.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("B")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==4){
        for(int x=piece.intX-1; verifiedPosition(x,piece.intY); x--){
            QString colorPiece = boxes[piece.intX][piece.intY]->pieceColor;
            QString colorNextPiece = boxes[x][piece.intY]->pieceColor;
            QString initialNextPiece = boxes[x][piece.intY]->initialLetter;
            //La siguiente pieza esta vacia
            if(colorNextPiece.compare("")==0){
                continue;
            }
            //La siguiente pieza es enemiga
            else if(colorPiece.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("R")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==5){
        for(int x=piece.intX-1, y=piece.intY-1; verifiedPosition(x,y); x--, y--){
            QString colorPiece = boxes[piece.intX][piece.intY]->pieceColor;
            QString colorNextPiece = boxes[x][y]->pieceColor;
            QString initialNextPiece = boxes[x][y]->initialLetter;
            //La siguiente pieza esta vacia
            if(colorNextPiece.compare("")==0){
                continue;
            }
            //La siguiente pieza es enemiga
            else if(colorPiece.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("B")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==6){
        for(int y=piece.intY-1; verifiedPosition(piece.intX,y); y--){
            QString colorPiece = boxes[piece.intX][piece.intY]->pieceColor;
            QString colorNextPiece = boxes[piece.intX][y]->pieceColor;
            QString initialNextPiece = boxes[piece.intX][y]->initialLetter;
            //La siguiente pieza esta vacia
            if(colorNextPiece.compare("")==0){
                continue;
            }
            //La siguiente pieza es enemiga
            else if(colorPiece.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("R")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    else if(direction==7){
        for(int x=piece.intX+1, y=piece.intY-1; verifiedPosition(x,y); x++, y--){
            QString colorPiece = boxes[piece.intX][piece.intY]->pieceColor;
            QString colorNextPiece = boxes[x][y]->pieceColor;
            QString initialNextPiece = boxes[x][y]->initialLetter;
            //La siguiente pieza esta vacia
            if(colorNextPiece.compare("")==0){
                continue;
            }
            //La siguiente pieza es enemiga
            else if(colorPiece.compare(colorNextPiece)!=0 && colorNextPiece.compare("")!=0 && (initialNextPiece.compare("B")==0 || initialNextPiece.compare("Q")==0)){
                return true;
            }
        }
    }
    return false;
}
