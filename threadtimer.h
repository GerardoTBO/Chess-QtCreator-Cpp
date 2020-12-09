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
signals:
    void seconds(int);
protected:
    void run();
private:
    int defaultTime = 10;
    int secondsTurn = 0;
    bool initialize = true;
};

#endif // THREADTIMER_H
