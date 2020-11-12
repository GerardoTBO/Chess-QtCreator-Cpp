#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets>
#include <QGridLayout>
#include <string>
#include <vector>
#include <iostream>
#include "piece.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include "horse.h"
#include "queen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void movePiece(int);

private:
    //Posiciones Guardadas
    int posiciones[2]={-1,-1};
    int turn = 1;
    //QPushButtons
    Piece* casillas[8][8];
    void assingPieces();
    QSignalMapper* signalMapper = new QSignalMapper (this);
    void createPiece(int,int,bool,QString,QString);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
