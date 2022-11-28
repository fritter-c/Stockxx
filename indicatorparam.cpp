#include "indicatorparam.h"

IndicatorParam::IndicatorParam()
{

}

IntegerParam::IntegerParam(int v)
{
    value = v;
}

DoubleParam::DoubleParam(double v)
{
    value = v;
}

ColorParam::ColorParam(QColor v)
{
    value = v;
}
