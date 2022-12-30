#include "movingaverage.h"


MovingAverage::MovingAverage(CustomSerie *base) : CustomArrayIndicator{base}
{

}


double MovingAverage::Value()
{
    return m_arData[0][m_nIndex].value;
}

QVector<double> MovingAverage::Values()
{
    QVector<double> result{Value()};
    return result;
}

void MovingAverage::resize(size_t n)
{
    m_arData[0].resize(n);
}

void MovingAverage::grow(size_t n)
{
    m_arData[0].resize(Size() + n);
}
