#include "builderpieces.h"

BuilderPieces::BuilderPieces(QSignalMapper* signalMapper,QGridLayout* boardGrid)
{
    this->signalMapper = signalMapper;
    this->boardGrid = boardGrid;
}
void BuilderPieces::createPiece(int x,int y,bool boxIsBlack,QString type, QString color,Piece* boxes[8][8]){
    //    ui->gridLayout->removeWidget(casillas[x][y]);

    //Creacion de piezas de algun tipo y asignacion de icono
    if(type.compare("")==0){
        boxes[x][y] = new Piece(color,"",boxIsBlack);
    }
    else if(type.compare("P")==0){
        boxes[x][y] = new Pawn(x,y,color,boxIsBlack);
    }
    else if(type.compare("B")==0){
        boxes[x][y] = new Bishop(x,y,color,boxIsBlack);
    }
    else if(type.compare("N")==0){
        boxes[x][y] = new Knight(x,y,color,boxIsBlack);
    }
    else if(type.compare("R")==0){
        boxes[x][y] = new Rook(x,y,color,boxIsBlack);
    }
    else if(type.compare("Q")==0){
        boxes[x][y] = new Queen(x,y,color,boxIsBlack);
    }
    else if(type.compare("K")==0){
        boxes[x][y] = new King(x,y,color,boxIsBlack);
    }
    boxes[x][y]->setIcon(QIcon(boxes[x][y]->imageDirection));
    boxes[x][y]->setIconSize(QSize(40,40));

    //Color del casilllero
    assingColorBackground(boxIsBlack,boxes[x][y]);

    //Agregar elementos a gridlayout
    boardGrid->addWidget(boxes[x][y],7-x,y);

    //Coneccion de eventos a Piece's
    connect (boxes[x][y], SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper -> setMapping (boxes[x][y], x*10+y);
}

void BuilderPieces::assingColorBackground(bool boxIsBlack,Piece* box){
    if(boxIsBlack){
        box->setStyleSheet("background-color: #540C0B;" "width: 60px;" "height:60px");
    }
    else{
        box->setStyleSheet("background-color: #DFB082;" "width: 60px;" "height:60px");
    }
}
