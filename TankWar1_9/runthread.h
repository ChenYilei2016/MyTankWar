#ifndef RUNTHREAD_H
#define RUNTHREAD_H

#include <QObject>
#include <QThread>
#include "tankclient.h"

/**
 *测试 在C++中用多线程的方式刷新界面/ 我用了定时器替换
 */
class TankClient;
class RunThread : public QThread
{
    Q_OBJECT
public:
    RunThread(TankClient* t);

    // QThread interface
protected:
    void run();

signals:
    void repaintSignals();

private :
    TankClient* tankclient;
};

#endif // RUNTHREAD_H
