#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGridLayout>
#include <QPushButton>
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton* casillas[8][8];
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            string temp;
            switch(j)
            {
            case 0: temp=to_string(i+1)+"a";
                break;
            case 1: temp=to_string(i+1)+"b";
                break;
            case 2: temp=to_string(i+1)+"c";
                break;
            case 3: temp=to_string(i+1)+"d";
                break;
            case 4: temp=to_string(i+1)+"e";
                break;
            case 5: temp=to_string(i+1)+"f";
                break;
            case 6: temp=to_string(i+1)+"g";
                break;
            case 7: temp=to_string(i+1)+"h";
                break;
            }
            casillas[i][j]=new QPushButton(temp.c_str());
            casillas[i][j]->setGeometry(0,0,50,50);
            ui->gridLayout->addWidget(casillas[i][j],9-i,j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

