#ifndef BUILDERPIECES_H
#define BUILDERPIECES_H
#include "piece.h"
#include <QGridLayout>
#include "piece.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include <QSignalMapper>


class BuilderPieces : public QObject
{
public:
    QSignalMapper* signalMapper;
    QGridLayout* boardGrid;

    BuilderPieces(QSignalMapper* signalMapper,QGridLayout* boardGrid);
    void createPiece(int,int,bool,QString, QString,Piece* boxes[8][8]);
    void assingColorBackground(bool,Piece*);
};

#endif // BUILDERPIECES_H
