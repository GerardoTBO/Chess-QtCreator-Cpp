#include "builderboard.h"

BuilderBoard::BuilderBoard(BuilderPieces* builderPieces)
{
    this->builderPieces = builderPieces;
}

void BuilderBoard::assingPieces(Piece* boxes[8][8],QString type){
    if(type.compare("reset")==0){
        resetBoard(boxes);
    }
    else if(type.compare("test")==0){
        testBoard(boxes);
    }
}
void BuilderBoard::testBoard(Piece* boxes[8][8]){
    //Piezas Blancas
//    builderPieces->createPiece(0,0,true,"R","white",boxes);
//    builderPieces->createPiece(0,1,false,"N","white",boxes);
//    builderPieces->createPiece(0,2,true,"B","white",boxes);
//    builderPieces->createPiece(0,3,false,"Q","white",boxes);
    builderPieces->createPiece(0,4,true,"K","white",boxes);
//    builderPieces->createPiece(0,5,false,"B","white",boxes);
//    builderPieces->createPiece(0,6,true,"N","white",boxes);
//    builderPieces->createPiece(0,7,false,"R","white",boxes);

    //Piezas Negras
//    builderPieces->createPiece(7,0,false,"R","black",boxes);
//    builderPieces->createPiece(7,1,true,"N","black",boxes);
//    builderPieces->createPiece(7,2,false,"B","black",boxes);
//    builderPieces->createPiece(7,3,true,"Q","black",boxes);
    builderPieces->createPiece(7,4,false,"K","black",boxes);
//    builderPieces->createPiece(7,5,true,"B","black",boxes);
//    builderPieces->createPiece(7,6,false,"N","black",boxes);
//    builderPieces->createPiece(7,7,true,"R","black",boxes);
}

void BuilderBoard::resetBoard(Piece* boxes[8][8]){
    //Piezas Blancas
    builderPieces->createPiece(0,0,true,"R","white",boxes);
    builderPieces->createPiece(0,1,false,"N","white",boxes);
    builderPieces->createPiece(0,2,true,"B","white",boxes);
    builderPieces->createPiece(0,3,false,"Q","white",boxes);
    builderPieces->createPiece(0,4,true,"K","white",boxes);
    builderPieces->createPiece(0,5,false,"B","white",boxes);
    builderPieces->createPiece(0,6,true,"N","white",boxes);
    builderPieces->createPiece(0,7,false,"R","white",boxes);

    builderPieces->createPiece(1,0,false,"P","white",boxes);
    builderPieces->createPiece(1,1,true,"P","white",boxes);
    builderPieces->createPiece(1,2,false,"P","white",boxes);
    builderPieces->createPiece(1,3,true,"P","white",boxes);
    builderPieces->createPiece(1,4,false,"P","white",boxes);
    builderPieces->createPiece(1,5,true,"P","white",boxes);
    builderPieces->createPiece(1,6,false,"P","white",boxes);
    builderPieces->createPiece(1,7,true,"P","white",boxes);

    //Piezas Negras
    builderPieces->createPiece(7,0,false,"R","black",boxes);
    builderPieces->createPiece(7,1,true,"N","black",boxes);
    builderPieces->createPiece(7,2,false,"B","black",boxes);
    builderPieces->createPiece(7,3,true,"Q","black",boxes);
    builderPieces->createPiece(7,4,false,"K","black",boxes);
    builderPieces->createPiece(7,5,true,"B","black",boxes);
    builderPieces->createPiece(7,6,false,"N","black",boxes);
    builderPieces->createPiece(7,7,true,"R","black",boxes);

    builderPieces->createPiece(6,0,true,"P","black",boxes);
    builderPieces->createPiece(6,1,false,"P","black",boxes);
    builderPieces->createPiece(6,2,true,"P","black",boxes);
    builderPieces->createPiece(6,3,false,"P","black",boxes);
    builderPieces->createPiece(6,4,true,"P","black",boxes);
    builderPieces->createPiece(6,5,false,"P","black",boxes);
    builderPieces->createPiece(6,6,true,"P","black",boxes);
    builderPieces->createPiece(6,7,false,"P","black",boxes);
}
