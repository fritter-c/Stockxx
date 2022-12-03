#include "customseriecalc.h"
#include "calcdaemon.h"

CustomSerieCalc::CustomSerieCalc()
{
    moveToThread(&CalcDaemon::Instance());
}
