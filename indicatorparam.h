#ifndef INDICATORPARAM_H
#define INDICATORPARAM_H


#include "qcolor.h"

class IndicatorParam
{
public:
    IndicatorParam();
};

class IntegerParam : public IndicatorParam
{
public:
    IntegerParam(int);
    int value;
};

class DoubleParam : public IndicatorParam
{
public:
    DoubleParam(double);
    double value;
};

class ColorParam : public IndicatorParam
{
public:
    ColorParam(QColor);
    QColor value;
};

#endif // INDICATORPARAM_H
