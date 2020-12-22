#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets>
#include <QGridLayout>
#include <vector>
#include <iostream>
#include "piece.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "dialogpawnpromotion.h"
#include "builderpieces.h"
#include "builderboard.h"
#include "Coordinate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ThreadTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void selectPiece(int);
    void saveLog();
    void changeTimer();
    void restartGame();
    void testGame();
    void controlTimer(int);
    void resigningWhite();
    void resigningBlack();
private:
    //Log
    QString textLog = "";
    QString lastMove = "";

    //Posiciones Guardadas
    int savedPosition[2]={-1,-1};
    int positionsWhiteCapture=0;
    int positionsBlackCapture=0;
    //Posiciones actuales de los reyes
    Coordinate positionWhiteKing;
    Coordinate positionBlackKing;

    //Turno actual
    int turn = 1;

    //Flag para resetear Timer
    bool resetTimer=false;

    //Flags de jake
    bool checkBlack = false;
    bool checkWhite = false;

    //QPushButtons
    Piece* boxes[8][8];

    //Piezas capturadas
    QLabel* whitePiecesCapture[16];
    QLabel* blackPiecesCapture[16];

    //Bloqueos
    bool flagGame = false;
    bool flagTimer = false;
    bool flagResetGame = false;

    QAction* optionTemporizador;

    ThreadTimer* timer;
    DialogPawnPromotion* dialogPromotion;

    QSignalMapper* signalMapper = new QSignalMapper (this);

    Ui::MainWindow *ui;

    BuilderPieces* builderPieces;
    BuilderBoard* builderBoard;

    void saveMove(int,int,int,int);
    void changeBackground(int,int);
    void restartBackground(int,int);
    void addPieceCapture(QString,QString);
    void restartTurn();
    void assingPiecesCapture();
    void promotion(int,int,QString);
    void addOptionsMenu();
    void clearPiecesCapture();
    void movePiece(int,int);
    void restartVariables();
    bool isCastling(int,int);
    void savePositionKing(int,int);

};
#endif // MAINWINDOW_H
