#include "dialogpawnpromotion.h"
#include "ui_dialogpawnpromotion.h"

DialogPawnPromotion::DialogPawnPromotion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPawnPromotion)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}
void DialogPawnPromotion::createIcons(QString color){
    pieces[0]=new QPushButton();
    pieces[0]->setIcon(QIcon("://pieces/"+color+"-queen.png"));
    pieces[0]->setIconSize(QSize(80,80));
    connect (pieces[0], SIGNAL(clicked()), this, SLOT(queen()));

    pieces[1]=new QPushButton();
    pieces[1]->setIcon(QIcon("://pieces/"+color+"-knight.png"));
    pieces[1]->setIconSize(QSize(80,80));
    connect (pieces[1], SIGNAL(clicked()), this, SLOT(knight()));

    pieces[2]=new QPushButton();
    pieces[2]->setIcon(QIcon("://pieces/"+color+"-rook.png"));
    pieces[2]->setIconSize(QSize(80,80));
    connect (pieces[2], SIGNAL(clicked()), this, SLOT(rook()));

    pieces[3]=new QPushButton();
    pieces[3]->setIcon(QIcon("://pieces/"+color+"-bishop.png"));
    pieces[3]->setIconSize(QSize(80,80));
    connect (pieces[3], SIGNAL(clicked()), this, SLOT(bishop()));

    for(int i=0;i<4;i++){
        ui->selectorPiece->addWidget(pieces[i],i/4,i%4);
    }

}
DialogPawnPromotion::~DialogPawnPromotion()
{
    delete ui;
}
void DialogPawnPromotion::queen(){
    election="Q";
    close();
}
void DialogPawnPromotion::bishop(){
    election="B";
    close();
}
void DialogPawnPromotion::knight(){
    election="N";
    close();
}
void DialogPawnPromotion::rook(){
    election="R";
    close();
}
