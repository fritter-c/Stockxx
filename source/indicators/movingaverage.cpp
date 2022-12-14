#include "movingaverage.h"


MovingAverage::MovingAverage(CustomSerie *base) : CustomArrayIndicator{base}
{

}

void MovingAverage::addNewValue(size_t start, size_t count, DoublyArray* values)
{
    if ((start == 0) and (count > 0))
        resize(count);
    else if (count > Size()) grow(Size() - count);

    for(size_t i{start}; i < count; ++i){
        for(long long j{0}; j < m_arData.count(); ++j){
            m_arData[j][i] = (*values)[j][i - start];
        }
    }
    emit NewData(start);
}

double MovingAverage::Value()
{
    return m_arData[0][m_nIndex];
}

void MovingAverage::resize(size_t n)
{
    m_arData[0].resize(n);
}

void MovingAverage::grow(size_t n)
{
    m_arData[0].resize(Size() + n);
}
