#include "timeseriesdaemon.h"
#include "qdebug.h"

void TimeSeriesDaemon::run()
{
    qDebug() << "Time Series Daemon started";
}

TimeSeriesDaemon::TimeSeriesDaemon(QObject *parent)
    : QThread{parent}
{

}
