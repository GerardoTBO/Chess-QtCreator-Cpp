#include "threadtimer.h"

ThreadTimer::ThreadTimer(QObject *parent) : QThread(parent)
{

}
ThreadTimer::~ThreadTimer(){

}

void ThreadTimer::run(){
    while(true){
        if(initialize){
            secondsTurn = defaultTime;
            initialize = false;
        }
        secondsTurn--;
        emit seconds(secondsTurn);
        msleep(950);
    }
}
void ThreadTimer::reset(){
    initialize = true;
}
