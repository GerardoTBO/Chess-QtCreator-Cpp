#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bool isBlack=true;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
//            std::string temp;
//            switch(j)
//            {
//            case 0: temp=std::to_string(i+1)+"a";
//                break;
//            case 1: temp=std::to_string(i+1)+"b";
//                break;
//            case 2: temp=std::to_string(i+1)+"c";
//                break;
//            case 3: temp=std::to_string(i+1)+"d";
//                break;
//            case 4: temp=std::to_string(i+1)+"e";
//                break;
//            case 5: temp=std::to_string(i+1)+"f";
//                break;
//            case 6: temp=std::to_string(i+1)+"g";
//                break;
//            case 7: temp=std::to_string(i+1)+"h";
//                break;
//            }
            createPiece(i,j,isBlack,"piece","");

            if(j!=7){
                isBlack=!isBlack;
            }
        }
    }
    //Coneccion Final de los Slots
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(movePiece(int)));

    //Crea todas las fichas en sus respectivas posiciones y colores
    assingPieces();
}

void MainWindow::createPiece(int x,int y,bool isBlack,QString tipo, QString color){
//    ui->gridLayout->removeWidget(casillas[x][y]);

    //Creacion de Ficha de algun tipo y asignacion de icono
    if(tipo.compare("piece")==0){
        casillas[x][y] = new Piece();
    }
    else if(tipo.compare("pawn")==0){
        casillas[x][y] = new Pawn(x,y);
        casillas[x][y]->dir_image= "://pieces/"+color+"-pawn.png";
    }
    else if(tipo.compare("bishop")==0){
        casillas[x][y] = new Bishop(x,y);
        casillas[x][y]->dir_image= "://pieces/"+color+"-bishop.png";
    }
    else if(tipo.compare("horse")==0){
        casillas[x][y] = new Horse(x,y);
        casillas[x][y]->dir_image= "://pieces/"+color+"-horse.png";
    }
    else if(tipo.compare("tower")==0){
        casillas[x][y] = new Rook(x,y);
        casillas[x][y]->dir_image= "://pieces/"+color+"-tower.png";
    }
    else if(tipo.compare("queen")==0){
        casillas[x][y] = new Queen(x,y);
        casillas[x][y]->dir_image= "://pieces/"+color+"-queen.png";
    }
    else if(tipo.compare("king")==0){
        casillas[x][y] = new King(x,y);
        casillas[x][y]->dir_image= "://pieces/"+color+"-king.png";
    }
    casillas[x][y]->piece_color = color;
    casillas[x][y]->class_name = tipo;
    casillas[x][y]->setIcon(QIcon(casillas[x][y]->dir_image));
    casillas[x][y]->setIconSize(QSize(40,40));

//    QString temp = QString::number(x) + " " + QString::number(y);
//    casillas[x][y]->setText(temp);

    //Color del casillleros
    if(isBlack){
        casillas[x][y]->setStyleSheet("background-color: #D7911E;" "width: 60px;" "height:60px");
    }
    else{
        casillas[x][y]->setStyleSheet("background-color: #FCD28B;" "width: 60px;" "height:60px");
    }
    ui->gridLayout->addWidget(casillas[x][y],7-x,y);

    //Coneccion de eventos a Piece's
    connect (casillas[x][y], SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper -> setMapping (casillas[x][y], x*10+y);
}

void MainWindow::movePiece(int c){
    //Calculo de posiciones por medio de c (i*10+j)
    int x = c/10;
    int y = c%10;

    if(casillas[x][y]->class_name.compare("")!=0 && ((casillas[x][y]->piece_color.compare("white")==0 && turn%2==1) || (casillas[x][y]->piece_color.compare("black")==0 && turn%2==0)) && posiciones[0]==-1 && posiciones[1]==-1){
        posiciones[0]=x;
        posiciones[1]=y;
        //Calcula las coordenadas donde se puede mover
        casillas[x][y]->wherePiece();
    }
    else if(posiciones[0]!=-1 && posiciones[1]!=-1){
        bool move_accept=false;
        //Itera en el vector de la piece casillas[posiciones[0]][posiciones[1] y verificar si se puede mover en esa nueva posicion
        for(std::size_t i=0;i<casillas[posiciones[0]][posiciones[1]]->fs.size();i++) {
            if(x==casillas[posiciones[0]][posiciones[1]]->fs[i].int_x && y==casillas[posiciones[0]][posiciones[1]]->fs[i].int_y){
                move_accept=true;
            }
        }

        //Realiza el movimiento
        if(move_accept){
            //Falta guardar datos, crear nuevas casillas al mover, y eliminar la permutacion

            //Permutacion de dir_imagen
            QString dir_temp = casillas[x][y]->dir_image;
            casillas[x][y]->dir_image = casillas[posiciones[0]][posiciones[1]]->dir_image;
            casillas[posiciones[0]][posiciones[1]]->dir_image = dir_temp;

            //Actualizacion de Iconos
            casillas[x][y]->setIcon(QIcon(casillas[x][y]->dir_image));
            casillas[posiciones[0]][posiciones[1]]->setIcon(QIcon(casillas[posiciones[0]][posiciones[1]]->dir_image));

            //Reinicio de posiciones guardadas y aumento de contador de turnos
            posiciones[0] = -1;
            posiciones[1] = -1;
            turn++;
        }
    }
}

void MainWindow::assingPieces(){
    //Fichas Blancas
    createPiece(0,0,true,"tower","white");
    createPiece(0,1,false,"horse","white");
    createPiece(0,2,true,"bishop","white");
    createPiece(0,3,false,"queen","white");
    createPiece(0,4,true,"king","white");
    createPiece(0,5,false,"bishop","white");
    createPiece(0,6,true,"horse","white");
    createPiece(0,7,false,"tower","white");

    createPiece(1,0,false,"pawn","white");
    createPiece(1,1,true,"pawn","white");
    createPiece(1,2,false,"pawn","white");
    createPiece(1,3,true,"pawn","white");
    createPiece(1,4,false,"pawn","white");
    createPiece(1,5,true,"pawn","white");
    createPiece(1,6,false,"pawn","white");
    createPiece(1,7,true,"pawn","white");

    //Fichas Negras
    createPiece(7,0,false,"tower","black");
    createPiece(7,1,true,"horse","black");
    createPiece(7,2,false,"bishop","black");
    createPiece(7,3,true,"queen","black");
    createPiece(7,4,false,"king","black");
    createPiece(7,5,true,"bishop","black");
    createPiece(7,6,false,"horse","black");
    createPiece(7,7,true,"tower","black");

    createPiece(6,0,true,"pawn","black");
    createPiece(6,1,false,"pawn","black");
    createPiece(6,2,true,"pawn","black");
    createPiece(6,3,false,"pawn","black");
    createPiece(6,4,true,"pawn","black");
    createPiece(6,5,false,"pawn","black");
    createPiece(6,6,true,"pawn","black");
    createPiece(6,7,false,"pawn","black");
}

MainWindow::~MainWindow()
{
    delete ui;
}


