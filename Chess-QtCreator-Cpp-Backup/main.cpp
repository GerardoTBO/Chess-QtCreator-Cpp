#include "mainwindow.h"

#include <QApplication>

#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "horse.h"
#include "rook.h"
#include "pawn.h"
#include "piece.h"
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    auto pawn = std::make_unique<Pawn>(7,3);
    pawn->wherePiece();
    //auto horse = std::make_unique<Horse>(2,1);
    //horse->wherePiece();
    //auto rook = std::make_unique<Rook>(1,1);
    //rook->wherePiece();
    //auto bishop = std::make_unique<Bishop>(4,3);
    //bishop->wherePiece();
    //auto queen = std::make_unique<Queen>(3,3);
    //queen->wherePiece();
    //auto king = std::make_unique<King>(5,3);
    //king->wherePiece();
    return a.exec();
}
