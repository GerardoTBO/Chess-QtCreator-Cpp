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
    void movePiece(int);
    void saveLog();
    void changeTimer();
    void restartGame();
private:
    //Log
    QString textLog = "";

    //Posiciones Guardadas
    int savedPosition[2]={-1,-1};
    int positionsWhiteCapture=0;
    int positionsBlackCapture=0;
    int turn = 1;

    //QPushButtons
    Piece* boxes[8][8];

    QLabel* whitePiecesCapture[16];
    QLabel* blackPiecesCapture[16];

    //Bloqueo
    bool flagPromotion = false;
    bool flagTimer = false;

    QAction* optionTemporizador;
    ThreadTimer* timer;
    DialogPawnPromotion* dialogPromotion;

    void saveMove(int,int,int,int);
    void assingPieces();
    QSignalMapper* signalMapper = new QSignalMapper (this);
    void createPiece(int,int,bool,QString,QString);
    void changeBackground(int,int);
    void restartBackground(int,int);
    void assingColorBackground(int,int,bool);
    void addPieceCapture(QString,QString);
    void restartTurn();
    void assingPiecesCapture();
    void promotion(int,int,QString);
    void addOptionsMenu();
    void clearPiecesCapture();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
