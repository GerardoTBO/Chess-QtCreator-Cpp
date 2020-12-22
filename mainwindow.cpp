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

    builderPieces = new BuilderPieces(signalMapper,ui->boardGrid);
    builderBoard = new BuilderBoard(builderPieces);

    //Asignar casillas para piezas capturadas
    assingPiecesCapture();

    //Restaurar
    restartGame();

    //Coneccion Final de los Slots
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(selectPiece(int)));

    //Agregar opciones en el menu
    addOptionsMenu();

    //Inicializar tiempo de turnos
    timer = new ThreadTimer(this);
    timer->start();

    connect(timer,SIGNAL(seconds(int)),this,SLOT(controlTimer(int)));

    connect(ui->resigningWhite,SIGNAL(clicked()),this,SLOT(resigningWhite()));
    connect(ui->resigningBlack,SIGNAL(clicked()),this,SLOT(resigningBlack()));
}

void MainWindow::controlTimer(int s){
    if(resetTimer){
        timer->reset();
        resetTimer = false;
    }
    else if(flagResetGame){
        timer->pause();
        restartGame();
        flagResetGame = false;
        timer->play();
    }
    else if(!flagGame && s==0 && turn%2==1){
        flagGame=true;
        QMessageBox::information(this,"Game Over","Jugador Blanco perdio por tiempo");
        flagGame=false;
        restartGame();
    }
    else if(!flagGame && s==0 && turn%2==0){
        flagGame=true;
        QMessageBox::information(this,"Game Over","Jugador Negro perdio por tiempo");
        flagGame=false;
        restartGame();
    }
    else if(turn%2==1){
        if(s%60<10){
            ui->timeLabel->setText("Tiempo de Blanco: "+QString::number(s/60)+":0"+QString::number(s%60));
        }
        else{
            ui->timeLabel->setText("Tiempo de Blanco: "+QString::number(s/60)+":"+QString::number(s%60));
        }

    }
    else if(turn%2==0){
        if(s%60<10){
            ui->timeLabel->setText("Tiempo de Negro: "+QString::number(s/60)+":0"+QString::number(s%60));
        }
        else{
            ui->timeLabel->setText("Tiempo de Negro: "+QString::number(s/60)+":"+QString::number(s%60));
        }

    }
}
void MainWindow::addOptionsMenu(){
    ui->menuChessGame->addAction("Guardar Log", this, SLOT (saveLog()));
    optionTemporizador = ui->menuChessGame->addAction("Desabilitar Timporizador", this, SLOT (changeTimer()));
    ui->menuChessGame->addAction("Reiniciar Juego", this, SLOT(restartGame()));
    ui->menuChessGame->addAction("Test",this,SLOT(testGame()));
}

void MainWindow::saveLog(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"log.txt",tr("Chess Log (*.txt)"));
    QFile file(fileName);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << textLog;
    }
}

void MainWindow::changeTimer(){
    flagTimer = !flagTimer;
    if(flagTimer){
        timer->pause();
        optionTemporizador->setText("Habilitar Temporizador");
        ui->timeLabel->setVisible(false);
    }
    else{
        timer->play();
        optionTemporizador->setText("Desabilitar Temporizador");
        ui->timeLabel->setVisible(true);
    }
}

void MainWindow::saveMove(int xO, int yO, int xF, int yF){
    //Agrega la posiciones inicial de la pieza movida
    lastMove = boxes[xO][yO]->initialLetter + QString::number(xO) + QString::number(yO);
    //Agrega x si se capturo una pieza enemiga
    if(boxes[xF][yF]->initialLetter.compare("")!=0){
        lastMove += "x";
    }
    //Agrega la posicion final de la pieza movida y un salto de linea
    lastMove += QString::number(xF) + QString::number(yO);
    textLog += lastMove + "\n";
    qDebug() << textLog;

}

void MainWindow::selectPiece(int c){
    //Calculo de posiciones por medio de c (i*10+j)
    int x = c/10;
    int y = c%10;

    //Selecciona pieza a mover
    if(!flagGame && boxes[x][y]->initialLetter.compare("")!=0 && ((boxes[x][y]->pieceColor.compare("white")==0 && turn%2==1) || (boxes[x][y]->pieceColor.compare("black")==0 && turn%2==0)) && savedPosition[0]==-1 && savedPosition[1]==-1){
        savedPosition[0]=x;
        savedPosition[1]=y;
        //Calcula las coordenadas donde se puede mover
        if(turn%2==1){
            boxes[x][y]->wherePiece(boxes,checkWhite,lastMove,positionWhiteKing);
        }
        else{
            boxes[x][y]->wherePiece(boxes,checkBlack,lastMove,positionBlackKing);
        }
        changeBackground(x,y);
    }

    //deseleccionar pieza
    else if(!flagGame && savedPosition[0]==x && savedPosition[1]==y){
        restartBackground(x,y);
        savedPosition[0]=-1;
        savedPosition[1]=-1;
    }

    //Cambia de pieza a mover
    else if(!flagGame && savedPosition[0]!=-1 && savedPosition[1]!=-1 && boxes[x][y]->pieceColor.compare(boxes[savedPosition[0]][savedPosition[1]]->pieceColor)==0 && !isCastling(x,y)){
        restartBackground(savedPosition[0],savedPosition[1]);
        savedPosition[0]=x;
        savedPosition[1]=y;
        //Calcula las coordenadas donde se puede mover
        if(turn%2==1){
            boxes[x][y]->wherePiece(boxes,checkWhite,lastMove,positionWhiteKing);
        }
        else{
            boxes[x][y]->wherePiece(boxes,checkBlack,lastMove,positionBlackKing);
        }
        changeBackground(x,y);
    }

    else if(!flagGame && savedPosition[0]!=-1 && savedPosition[1]!=-1){
        bool moveAccepted=false;
        //Itera en el vector de la piece casillas[posiciones[0]][posiciones[1] y verificar si se puede mover en esa nueva posicion
        for(std::size_t i=0;i<boxes[savedPosition[0]][savedPosition[1]]->possibleMovements.size();i++) {
            if(x==boxes[savedPosition[0]][savedPosition[1]]->possibleMovements[i].intX && y==boxes[savedPosition[0]][savedPosition[1]]->possibleMovements[i].intY){
                moveAccepted=true;
            }
        }

        //Pre movimiento
        if(moveAccepted){

            //Limpia los background
            restartBackground(savedPosition[0],savedPosition[1]);

            //Realiza movimiento
            movePiece(x,y);

            //Reinicio de posiciones guardadas y aumento de contador de turnos
            savedPosition[0] = -1;
            savedPosition[1] = -1;
            turn++;
            timer->changeTurn();
        }
    }

}

bool MainWindow::isCastling(int x, int y){
    if(boxes[savedPosition[0]][savedPosition[1]]->firstStep && boxes[x][y]->initialLetter.compare("R")==0 && boxes[savedPosition[0]][savedPosition[1]]->initialLetter.compare("K")==0){
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::movePiece(int x,int y){

    //Agrega la pieza capturada de forma normal y comprueba si es un rey o no
    if(boxes[x][y]->initialLetter.compare("")!=0 && boxes[x][y]->pieceColor.compare(boxes[savedPosition[0]][savedPosition[1]]->pieceColor)!=0){
        addPieceCapture(boxes[x][y]->pieceColor,boxes[x][y]->imageDirection);
        if(boxes[x][y]->initialLetter.compare("K")==0 && turn%2==1){
            flagGame=true;
            QMessageBox::information(this,"Game Over","Jugador Blanco gana");
            flagResetGame=true;
            flagGame=false;
        }
        else if(boxes[x][y]->initialLetter.compare("K")==0 && turn%2==0){
            flagGame=true;
            QMessageBox::information(this,"Game Over","Jugador Negro gana");
            flagResetGame=true;
            flagGame=false;
        }
    }

    //Calcula movimiento normales y especiales

    //Peon promovido
    if(boxes[savedPosition[0]][savedPosition[1]]->initialLetter.compare("P")==0 && ((boxes[savedPosition[0]][savedPosition[1]]->pieceColor.compare("white")==0 && x==7) || (boxes[savedPosition[0]][savedPosition[1]]->pieceColor.compare("black")==0 && x==0))){
        //Guarda en el log
        saveMove(savedPosition[0],savedPosition[1],x,y);
        if(!flagResetGame){
            promotion(x,y,boxes[savedPosition[0]][savedPosition[1]]->pieceColor);
        }
        boxes[x][y]->useFirsStep();
        builderPieces->createPiece(savedPosition[0],savedPosition[1],boxes[savedPosition[0]][savedPosition[1]]->backgroundColor,"","",boxes);

    }
    //Peon Pasando
    else if(boxes[savedPosition[0]][savedPosition[1]]->initialLetter.compare("P")==0 && boxes[x][y]->initialLetter.compare("")==0 && savedPosition[1]!=y){
        if(boxes[savedPosition[0]][savedPosition[1]]->pieceColor.compare("white")==0){
            addPieceCapture(boxes[x-1][y]->pieceColor,boxes[x-1][y]->imageDirection);
            //Moviendo peon que esta pasando
            builderPieces->createPiece(x,y,boxes[x][y]->backgroundColor,"P",boxes[savedPosition[0]][savedPosition[1]]->pieceColor,boxes);
            //Limpiando casilla de donde viene el peon
            builderPieces->createPiece(savedPosition[0],savedPosition[1],boxes[savedPosition[0]][savedPosition[1]]->backgroundColor,"","",boxes);
            //Limpiando el lugar donde estaba el peon sobre el que se paso
            builderPieces->createPiece(x-1,y,boxes[x-1][y]->backgroundColor,"","",boxes);
            boxes[x][y]->useFirsStep();
        }
        else{
            addPieceCapture(boxes[x+1][y]->pieceColor,boxes[x+1][y]->imageDirection);
            builderPieces->createPiece(x,y,boxes[x][y]->backgroundColor,"P",boxes[savedPosition[0]][savedPosition[1]]->pieceColor,boxes);
            builderPieces->createPiece(savedPosition[0],savedPosition[1],boxes[savedPosition[0]][savedPosition[1]]->backgroundColor,"","",boxes);
            builderPieces->createPiece(x+1,y,boxes[x+1][y]->backgroundColor,"","",boxes);
            boxes[x][y]->useFirsStep();
        }
    }
    //Enroque
    else if(isCastling(x,y)){
        if(y<savedPosition[1]){
            //Moviendo rey
            builderPieces->createPiece(x,savedPosition[1]-2,boxes[x][savedPosition[1]-2]->backgroundColor,"K",boxes[savedPosition[0]][savedPosition[1]]->pieceColor,boxes);
            builderPieces->createPiece(savedPosition[0],savedPosition[1],boxes[savedPosition[0]][savedPosition[1]]->backgroundColor,"","",boxes);
            boxes[x][savedPosition[1]-2]->useFirsStep();
            //Moviendo torre
            builderPieces->createPiece(x,y+3,boxes[x][y+3]->backgroundColor,"R",boxes[x][y]->pieceColor,boxes);
            builderPieces->createPiece(x,y,boxes[x][y]->backgroundColor,"","",boxes);
            boxes[x][y+3]->useFirsStep();
            textLog += "0-0-0\n";
        }
        else{
            //Moviendo rey
            builderPieces->createPiece(x,savedPosition[1]+2,boxes[x][savedPosition[1]+2]->backgroundColor,"K",boxes[savedPosition[0]][savedPosition[1]]->pieceColor,boxes);
            builderPieces->createPiece(savedPosition[0],savedPosition[1],boxes[savedPosition[0]][savedPosition[1]]->backgroundColor,"","",boxes);
            boxes[x][savedPosition[1]+2]->useFirsStep();
            //Moviendo torre
            builderPieces->createPiece(x,y-2,boxes[x][y-2]->backgroundColor,"R",boxes[x][y]->pieceColor,boxes);
            builderPieces->createPiece(x,y,boxes[x][y]->backgroundColor,"","",boxes);
            boxes[x][y-2]->useFirsStep();
            textLog += "0-0\n";
        }
    }
    //Movimiento Normal
    else{
        //Guarda en el log
        saveMove(savedPosition[0],savedPosition[1],x,y);

        //Mueve la pieza a la nueva casilla
        builderPieces->createPiece(x,y,boxes[x][y]->backgroundColor,boxes[savedPosition[0]][savedPosition[1]]->initialLetter,boxes[savedPosition[0]][savedPosition[1]]->pieceColor,boxes);

        //Limpia la anterior casillas
        builderPieces->createPiece(savedPosition[0],savedPosition[1],boxes[savedPosition[0]][savedPosition[1]]->backgroundColor,"","",boxes);

        //Marca la pieza como movida
        boxes[x][y]->useFirsStep();

        //Si es rey guarda su posicion actual
        savePositionKing(x,y);
    }

    //Calcula si algun rey esta en jake
    //boxes[x][y]->wherePiece(boxes,true,true);
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
    builderPieces->assingColorBackground(boxes[x][y]->backgroundColor,boxes[x][y]);
    for(std::size_t i=0;i<boxes[x][y]->possibleMovements.size();i++) {
        int pX = boxes[x][y]->possibleMovements[i].intX;
        int pY = boxes[x][y]->possibleMovements[i].intY;
        builderPieces->assingColorBackground(boxes[pX][pY]->backgroundColor,boxes[pX][pY]);
    }
}

void MainWindow::savePositionKing(int x,int y){
    if(boxes[x][y]->initialLetter.compare("K")==0 && turn%2==1){
        positionWhiteKing.intX = x;
        positionWhiteKing.intY = y;
        qDebug() << "W x: "<< positionWhiteKing.intX << " y: " << positionWhiteKing.intY << "\n";
    }
    else if(boxes[x][y]->initialLetter.compare("K")==0 && turn%2==0){
        positionBlackKing.intX = x;
        positionBlackKing.intY = y;
        qDebug() << "B x: "<< positionBlackKing.intX << " y: " << positionBlackKing.intY << "\n";
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

void MainWindow::clearPiecesCapture(){
    for(int i=0;i<16;i++){
        whitePiecesCapture[i]->clear();
        blackPiecesCapture[i]->clear();
    }
}
void MainWindow::restartVariables(){
    //Variables
    resetTimer = true;
    textLog = "";
    savedPosition[0]=-1;
    savedPosition[1]=-1;
    positionsWhiteCapture=0;
    positionsBlackCapture=0;
    turn = 1;
    //Coordenadas actual de los reyes
    positionWhiteKing.intX = 0;
    positionWhiteKing.intY = 4;

    positionBlackKing.intX = 7;
    positionBlackKing.intY = 4;
}

void MainWindow::restartGame(){
    restartVariables();

    //Crear Tablero vacio
    bool boxIsBlack=true;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            builderPieces->createPiece(i,j,boxIsBlack,"","",boxes);
            if(j!=7){
                boxIsBlack=!boxIsBlack;
            }
        }
    }

    //Crea todas las piezas en sus respectivas posiciones y colores
    builderBoard->assingPieces(boxes,"reset");

    //Limpiar Casillas de Pieza Capturadas
    clearPiecesCapture();

}

void MainWindow::testGame(){
    restartVariables();

    //Crear Tablero vacio
    bool boxIsBlack=true;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            builderPieces->createPiece(i,j,boxIsBlack,"","",boxes);
            if(j!=7){
                boxIsBlack=!boxIsBlack;
            }
        }
    }
    builderBoard->assingPieces(boxes,"test");
    clearPiecesCapture();
}
void MainWindow::promotion(int x,int y, QString color){
    timer->pause();
    flagGame = true;
    dialogPromotion = new DialogPawnPromotion(this);
    dialogPromotion->createIcons(color);
    dialogPromotion->exec();
    //creacion de nueva pieza
    builderPieces->createPiece(x,y,boxes[x][y]->backgroundColor,dialogPromotion->election,color,boxes);
    //guardar log
    textLog += QString::number(x)+QString::number(y)+dialogPromotion->election+"\n";
    //Desbloqueo
    flagGame = false;
    timer->play();
}
void MainWindow::resigningWhite(){
    QMessageBox::information(this,"Game Over","Jugador Blanco se rindio");
    restartGame();
}
void MainWindow::resigningBlack(){
    QMessageBox::information(this,"Game Over","Jugador Negro se rindio");
    restartGame();
}
MainWindow::~MainWindow()
{
    timer->terminate();
    delete ui;
}



