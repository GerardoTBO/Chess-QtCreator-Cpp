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
    /*
    QPalette pal= button.palette();
    pal.setColor(QPalette::Window, QColor(255, 0, 0));
    pal.setColor(QPalette::Button, QColor(0x00, 0x00, 0xff));
    pal.setColor(QPalette::ButtonText, QColor(Qt::yellow));
    */
    QPushButton* casillas[8][8];
    bool isBlack=true;
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
            // 2. casillas[i][j]->setStyleSheet("background-color: #554D44;" "width: 60px;" "height:60px");
            // 2. casillas[i][j]->setStyleSheet("background-color: #EAB467;" "width: 60px;" "height:60px");
            // 3. casillas[i][j]->setStyleSheet("background-color: #362523;" "width: 60px;" "height:60px");
            // 3. casillas[i][j]->setStyleSheet("background-color: #EECEB2;" "width: 60px;" "height:60px");
            // 4. casillas[i][j]->setStyleSheet("background-color: #3B3B3B;" "width: 60px;" "height:60px");
            // 4. casillas[i][j]->setStyleSheet("background-color: #DADFDF;" "width: 60px;" "height:60px");
            // 5. casillas[i][j]->setStyleSheet("background-color: #8D8C9A;" "width: 60px;" "height:60px");
            // 5. casillas[i][j]->setStyleSheet("background-color: #D7D5E1;" "width: 60px;" "height:60px");
            // 6. casillas[i][j]->setStyleSheet("background-color: #7794A9;" "width: 60px;" "height:60px");
            // 6. casillas[i][j]->setStyleSheet("background-color: #D63E12;" "width: 60px;" "height:60px");
            // 7. casillas[i][j]->setStyleSheet("background-color: #4B443B;" "width: 60px;" "height:60px");
            // 7. casillas[i][j]->setStyleSheet("background-color: #FBF5EC;" "width: 60px;" "height:60px");
            // 8. casillas[i][j]->setStyleSheet("background-color: #454831;" "width: 60px;" "height:60px");
            // 8. casillas[i][j]->setStyleSheet("background-color: #D2B089;" "width: 60px;" "height:60px");
            // 9. casillas[i][j]->setStyleSheet("background-color: #252A28;" "width: 60px;" "height:60px");
            // 9. casillas[i][j]->setStyleSheet("background-color: #6C8381;" "width: 60px;" "height:60px");
            // 10. casillas[i][j]->setStyleSheet("background-color: #626364;" "width: 60px;" "height:60px");
            // 10. casillas[i][j]->setStyleSheet("background-color: #A65B51;" "width: 60px;" "height:60px");
            // 11. casillas[i][j]->setStyleSheet("background-color: #BC5351;" "width: 60px;" "height:60px");
            // 11. casillas[i][j]->setStyleSheet("background-color: #C1C2EE;" "width: 60px;" "height:60px");
            // 12. casillas[i][j]->setStyleSheet("background-color: #6F809E;" "width: 60px;" "height:60px");
            // 12. casillas[i][j]->setStyleSheet("background-color: #D2CDB9;" "width: 60px;" "height:60px");
            if(isBlack){
                casillas[i][j]->setStyleSheet("background-color: #540C0B;" "width: 60px;" "height:60px");
            }
            else{
                casillas[i][j]->setStyleSheet("background-color: #DFB082;" "width: 60px;" "height:60px");
            }
            if(j!=7){
                isBlack=!isBlack;
            }

            ui->gridLayout->addWidget(casillas[i][j],9-i,j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

