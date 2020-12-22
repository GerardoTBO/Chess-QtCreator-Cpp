#include "threadtimer.h"


ThreadTimer::ThreadTimer(QObject *parent) : QThread(parent)
{

}
ThreadTimer::~ThreadTimer(){

}

void ThreadTimer::run(){
    while(true){
        if(initialize){
            whiteTime = defaultTime;
            blackTime = defaultTime;
            initialize = false;
        }
        if(!flagGame){
            if(turn%2==1){
                if(whiteTime!=0){
                    whiteTime--;
                }
                emit seconds(whiteTime);
            }

            else if(turn%2==0){
                if(blackTime!=0){
                    blackTime--;
                }
                emit seconds(blackTime);
            }
        }
        msleep(950);
    }
}
void ThreadTimer::reset(){
    initialize = true;
}
void ThreadTimer::changeTurn(){
    turn++;
}
void ThreadTimer::play(){
    flagGame = false;
}
void ThreadTimer::pause(){
    flagGame = true;
}
