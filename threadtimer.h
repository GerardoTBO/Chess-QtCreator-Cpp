#ifndef THREADTIMER_H
#define THREADTIMER_H

#include <QThread>

class ThreadTimer : public QThread
{
    Q_OBJECT
public:
    ThreadTimer(QObject *parent = 0);
    ~ThreadTimer();
    void reset();
    void play();
    void pause();
    void changeTurn();
signals:
    void seconds(int);
protected:
    void run();
private:
    bool flagGame = false;
    int defaultTime = 2400;
    int whiteTime = 0;
    int blackTime = 0;
    int turn = 1;
    bool initialize = true;
};

#endif // THREADTIMER_H
