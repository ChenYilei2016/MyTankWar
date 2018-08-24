#include "runthread.h"
#include <windows.h>
#include <QDebug>

RunThread::RunThread(TankClient *t)
:tankclient(t)
{

}

void RunThread::run()
{
    while(true)
    {
        emit repaintSignals();
        Sleep(46);
    }
}
