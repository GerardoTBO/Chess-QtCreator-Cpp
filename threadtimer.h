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
signals:
    void seconds(int);
protected:
    void run();
private:
    bool flagPromotion = false;
    int defaultTime = 180;
    int secondsTurn = 0;
    bool initialize = true;
};

#endif // THREADTIMER_H
