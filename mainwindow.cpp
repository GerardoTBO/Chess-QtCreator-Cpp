#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtDebug>
#include "threadtimer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Disable resize window
    this->setFixedSize(this->width(), this->height());

    bool boxIsBlack=true;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            createPiece(i,j,boxIsBlack,"","");

            if(j!=7){
                boxIsBlack=!boxIsBlack;
            }
        }
    }
    //Coneccion Final de los Slots
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(movePiece(int)));

    //Crea todas las piezas en sus respectivas posiciones y colores
    assingPieces();

    //Casillas de Pieza Capturadas
    assingPiecesCapture();

    //Inicializar tiempo de turnos
    timer = new ThreadTimer(this);
    timer->start();
    connect(timer, &ThreadTimer::seconds, [&](int s){
        if(s==0){
            timer->reset();
            turn++;
            if(savedPosition[0]!=-1 && savedPosition[1]!=-1){
                restartBackground(savedPosition[0],savedPosition[1]);
                savedPosition[0]=-1;
                savedPosition[1]=-1;
            }
            textLog += "skipTurn ";
        }
        ui->timeLabel->setText(QString::number(s/60)+":"+QString::number(s%60));
    });
}

void MainWindow::createPiece(int x,int y,bool boxIsBlack,QString type, QString color){
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
    assingColorBackground(x,y,boxIsBlack);

    //Agregar elementos a gridlayout
    ui->boardGrid->addWidget(boxes[x][y],7-x,y);

    //Coneccion de eventos a Piece's
    connect (boxes[x][y], SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper -> setMapping (boxes[x][y], x*10+y);
}

void MainWindow::saveMove(int xO, int yO, int xF, int yF){
    //Agrega la posiciones inicial de la pieza movida
    textLog += boxes[xO][yO]->initialLetter + QString::number(xO) + QString::number(yO);
    //Agrega x si se capturo una pieza enemiga
    if(boxes[xF][yF]->initialLetter.compare("")!=0){
        textLog += "x";
    }
    //Agrega la posicion final de la pieza movida y un salto de linea
    textLog += QString::number(xF) + QString::number(yO) + " ";
    qDebug() << textLog;
}

void MainWindow::movePiece(int c){
    //Calculo de posiciones por medio de c (i*10+j)
    int x = c/10;
    int y = c%10;

    //Selecciona pieza a mover
    if(!flagPromotion && boxes[x][y]->initialLetter.compare("")!=0 && ((boxes[x][y]->pieceColor.compare("white")==0 && turn%2==1) || (boxes[x][y]->pieceColor.compare("black")==0 && turn%2==0)) && savedPosition[0]==-1 && savedPosition[1]==-1){
        savedPosition[0]=x;
        savedPosition[1]=y;
        //Calcula las coordenadas donde se puede mover
        boxes[x][y]->wherePiece(boxes,true,false);
        changeBackground(x,y);
    }

    //deseleccionar pieza
    else if(!flagPromotion && savedPosition[0]==x && savedPosition[1]==y){
        restartBackground(x,y);
        savedPosition[0]=-1;
        savedPosition[1]=-1;
    }

    //Cambia de pieza a mover
    else if(!flagPromotion && savedPosition[0]!=-1 && savedPosition[1]!=-1 && boxes[x][y]->pieceColor.compare(boxes[savedPosition[0]][savedPosition[1]]->pieceColor)==0){
        restartBackground(savedPosition[0],savedPosition[1]);
        savedPosition[0]=x;
        savedPosition[1]=y;
        //Calcula las coordenadas donde se puede mover
        boxes[x][y]->wherePiece(boxes,true,false);
        changeBackground(x,y);
    }

    else if(!flagPromotion && savedPosition[0]!=-1 && savedPosition[1]!=-1){
        bool moveAccepted=false;
        //Itera en el vector de la piece casillas[posiciones[0]][posiciones[1] y verificar si se puede mover en esa nueva posicion
        for(std::size_t i=0;i<boxes[savedPosition[0]][savedPosition[1]]->possibleMovements.size();i++) {
            if(x==boxes[savedPosition[0]][savedPosition[1]]->possibleMovements[i].intX && y==boxes[savedPosition[0]][savedPosition[1]]->possibleMovements[i].intY){
                moveAccepted=true;
            }
        }

        //Realiza el movimiento
        if(moveAccepted){
            //Guarda en el log
            saveMove(savedPosition[0],savedPosition[1],x,y);

            //Limpia los background
            restartBackground(savedPosition[0],savedPosition[1]);

            //Agrega la pieza capturada
            if(boxes[x][y]->initialLetter.compare("")!=0 && boxes[x][y]->pieceColor.compare(boxes[savedPosition[0]][savedPosition[1]]->pieceColor)!=0){
                addPieceCapture(boxes[x][y]->pieceColor,boxes[x][y]->imageDirection);
            }
            //Mueve la pieza a la nueva casilla
            createPiece(x,y,boxes[x][y]->backgroundColor,boxes[savedPosition[0]][savedPosition[1]]->initialLetter,boxes[savedPosition[0]][savedPosition[1]]->pieceColor);
            //Marca la pieza como movida
            boxes[x][y]->useFirsStep();
            //Calcula si algun rey esta en jake
            boxes[x][y]->wherePiece(boxes,true,true);
            //Limpia la anterior casillas
            createPiece(savedPosition[0],savedPosition[1],boxes[savedPosition[0]][savedPosition[1]]->backgroundColor,"","");
            //Prueba de promocion
            promotion(x,y,boxes[x][y]->pieceColor);
            //Reinicio de posiciones guardadas y aumento de contador de turnos
            savedPosition[0] = -1;
            savedPosition[1] = -1;
            turn++;
            timer->reset();

        }
    }

}

void MainWindow::addPieceCapture(QString color, QString image){
    if(color.compare("black")==0){
        blackPiecesCapture[positionsBlackCapture]->setPixmap(QPixmap::fromImage(QImage(image).scaled(30,50)));
        positionsBlackCapture++;
    }
    else if(color.compare("white")==0){
        whitePiecesCapture[positionsWhiteCapture]->setPixmap(QPixmap::fromImage(QImage(image).scaled(30,50)));
        positionsWhiteCapture++;
    }
}

void MainWindow::changeBackground(int x,int y){
    boxes[x][y]->setStyleSheet("background-color: #7E3B3A;" "width: 60px;" "height:60px");
    for(std::size_t i=0;i<boxes[x][y]->possibleMovements.size();i++) {
        boxes[boxes[x][y]->possibleMovements[i].intX][boxes[x][y]->possibleMovements[i].intY]->setStyleSheet("background-color: #C48E8D;" "width: 60px;" "height:60px");
    }
}

void MainWindow::restartBackground(int x,int y){
    assingColorBackground(x,y,boxes[x][y]->backgroundColor);
    for(std::size_t i=0;i<boxes[x][y]->possibleMovements.size();i++) {
        assingColorBackground(boxes[x][y]->possibleMovements[i].intX,boxes[x][y]->possibleMovements[i].intY,boxes[boxes[x][y]->possibleMovements[i].intX][boxes[x][y]->possibleMovements[i].intY]->backgroundColor);
    }
}

void MainWindow::assingColorBackground(int x,int y,bool boxIsBlack){
    if(boxIsBlack){
        boxes[x][y]->setStyleSheet("background-color: #540C0B;" "width: 60px;" "height:60px");
    }
    else{
        boxes[x][y]->setStyleSheet("background-color: #DFB082;" "width: 60px;" "height:60px");
    }
}

void MainWindow::assingPiecesCapture(){
    for(int i=0;i<16;i++){
        int x = i/4;
        int y = i%4;

        whitePiecesCapture[i]=new QLabel();
        whitePiecesCapture[i]->setStyleSheet("width: 30px;" "height:50px;" "background-color:rgba( 255, 255, 255, 0%);" "border:none;");
        whitePiecesCapture[i]->setAlignment(Qt::AlignCenter);
        ui->captureWhitePiecesGrid->addWidget(whitePiecesCapture[i],x,y,Qt::AlignTop);

        blackPiecesCapture[i]=new QLabel();
        blackPiecesCapture[i]->setStyleSheet("width: 30px;" "height:50px;" "background-color:rgba( 255, 255, 255, 0%);" "border:none;");
        blackPiecesCapture[i]->setAlignment(Qt::AlignCenter);
        ui->captureBlackPiecesGrid->addWidget(blackPiecesCapture[i],x,y,Qt::AlignTop);
    }

}

void MainWindow::promotion(int x,int y, QString color){
    timer->pause();
    flagPromotion = true;
    dialogPromotion = new DialogPawnPromotion(this);
    dialogPromotion->createIcons(color);
    dialogPromotion->exec();
    //creacion de nueva pieza
    createPiece(x,y,boxes[x][y]->backgroundColor,dialogPromotion->election,color);
    //Desbloqueo
    flagPromotion = false;
    timer->play();
}

void MainWindow::assingPieces(){
    //Piezas Blancas
    createPiece(0,0,true,"R","white");
    createPiece(0,1,false,"N","white");
    createPiece(0,2,true,"B","white");
    createPiece(0,3,false,"Q","white");
    createPiece(0,4,true,"K","white");
    createPiece(0,5,false,"B","white");
    createPiece(0,6,true,"N","white");
    createPiece(0,7,false,"R","white");

    createPiece(1,0,false,"P","white");
    createPiece(1,1,true,"P","white");
    createPiece(1,2,false,"P","white");
    createPiece(1,3,true,"P","white");
    createPiece(1,4,false,"P","white");
    createPiece(1,5,true,"P","white");
    createPiece(1,6,false,"P","white");
    createPiece(1,7,true,"P","white");

    //Piezas Negras
    createPiece(7,0,false,"R","black");
    createPiece(7,1,true,"N","black");
    createPiece(7,2,false,"B","black");
    createPiece(7,3,true,"Q","black");
    createPiece(7,4,false,"K","black");
    createPiece(7,5,true,"B","black");
    createPiece(7,6,false,"N","black");
    createPiece(7,7,true,"R","black");

    createPiece(6,0,true,"P","black");
    createPiece(6,1,false,"P","black");
    createPiece(6,2,true,"P","black");
    createPiece(6,3,false,"P","black");
    createPiece(6,4,true,"P","black");
    createPiece(6,5,false,"P","black");
    createPiece(6,6,true,"P","black");
    createPiece(6,7,false,"P","black");
}

MainWindow::~MainWindow()
{
    delete ui;
}



