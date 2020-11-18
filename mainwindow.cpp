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
        casillas[x][y] = new Piece("",color,tipo,isBlack);
    }
    else if(tipo.compare("pawn")==0){
        casillas[x][y] = new Pawn(x,y,"://pieces/"+color+"-pawn.png",color,tipo,isBlack);
    }
    else if(tipo.compare("bishop")==0){
        casillas[x][y] = new Bishop(x,y,"://pieces/"+color+"-bishop.png",color,tipo,isBlack);
    }
    else if(tipo.compare("horse")==0){
        casillas[x][y] = new Horse(x,y,"://pieces/"+color+"-horse.png",color,tipo,isBlack);
    }
    else if(tipo.compare("tower")==0){
        casillas[x][y] = new Rook(x,y,"://pieces/"+color+"-tower.png",color,tipo,isBlack);
    }
    else if(tipo.compare("queen")==0){
        casillas[x][y] = new Queen(x,y,"://pieces/"+color+"-queen.png",color,tipo,isBlack);
    }
    else if(tipo.compare("king")==0){
        casillas[x][y] = new King(x,y,"://pieces/"+color+"-king.png",color,tipo,isBlack);
    }
    casillas[x][y]->setIcon(QIcon(casillas[x][y]->dir_image));
    casillas[x][y]->setIconSize(QSize(40,40));

    //    QString temp = QString::number(x) + " " + QString::number(y);
    //    casillas[x][y]->setText(temp);

    //Color del casilllero
    assingColorBackground(x,y,isBlack);

    //Agregar elementos a gridlayout
    ui->gridLayout->addWidget(casillas[x][y],7-x,y);

    //Coneccion de eventos a Piece's
    connect (casillas[x][y], SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper -> setMapping (casillas[x][y], x*10+y);
}

void MainWindow::movePiece(int c){
    //Calculo de posiciones por medio de c (i*10+j)
    int x = c/10;
    int y = c%10;

    //Selecciona ficha a mover
    if(casillas[x][y]->class_name.compare("")!=0 && ((casillas[x][y]->piece_color.compare("white")==0 && turn%2==1) || (casillas[x][y]->piece_color.compare("black")==0 && turn%2==0)) && posiciones[0]==-1 && posiciones[1]==-1){
        posiciones[0]=x;
        posiciones[1]=y;
        //Calcula las coordenadas donde se puede mover
        casillas[x][y]->wherePiece();
        changeBackground(x,y);
    }

    //Cambia de ficha a mover
    else if(posiciones[0]!=-1 && posiciones[1]!=-1 && casillas[x][y]->piece_color.compare(casillas[posiciones[0]][posiciones[1]]->piece_color)==0){
        restartBackground(posiciones[0],posiciones[1]);
        posiciones[0]=x;
        posiciones[1]=y;
        //Calcula las coordenadas donde se puede mover
        casillas[x][y]->wherePiece();
        changeBackground(x,y);
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
            //Limpia los background
            restartBackground(posiciones[0],posiciones[1]);
            //Mueve la pieza a la nueva casilla
            createPiece(x,y,casillas[x][y]->background_color,casillas[posiciones[0]][posiciones[1]]->class_name,casillas[posiciones[0]][posiciones[1]]->piece_color);
            //Limpia la anterior casillas
            createPiece(posiciones[0],posiciones[1],casillas[posiciones[0]][posiciones[1]]->background_color,"piece","");
            //Reinicio de posiciones guardadas y aumento de contador de turnos
            posiciones[0] = -1;
            posiciones[1] = -1;
            turn++;
        }
    }
}

void MainWindow::changeBackground(int x,int y){
    casillas[x][y]->setStyleSheet("background-color: #7E3B3A;" "width: 60px;" "height:60px");
    for(std::size_t i=0;i<casillas[x][y]->fs.size();i++) {
        casillas[casillas[x][y]->fs[i].int_x][casillas[x][y]->fs[i].int_y]->setStyleSheet("background-color: #C48E8D;" "width: 60px;" "height:60px");
    }
}

void MainWindow::restartBackground(int x,int y){
    assingColorBackground(x,y,casillas[x][y]->background_color);
    for(std::size_t i=0;i<casillas[x][y]->fs.size();i++) {
        assingColorBackground(casillas[x][y]->fs[i].int_x,casillas[x][y]->fs[i].int_y,casillas[casillas[x][y]->fs[i].int_x][casillas[x][y]->fs[i].int_y]->background_color);
    }
}

void MainWindow::assingColorBackground(int x,int y,bool isBlack){
    if(isBlack){
        casillas[x][y]->setStyleSheet("background-color: #540C0B;" "width: 60px;" "height:60px");
    }
    else{
        casillas[x][y]->setStyleSheet("background-color: #DFB082;" "width: 60px;" "height:60px");
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



