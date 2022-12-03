#include "calcdaemon.h"

CalcDaemon* CalcDaemon::instance = nullptr;

CalcDaemon::CalcDaemon(QObject *parent)
    : QThread{parent}
{
    assert(instance == nullptr);
    instance = this;
    setObjectName("Calc");
}
