#include "singlysizedindicator.h"

SinglySizedIndicator::SinglySizedIndicator() : IndicatorData{}
{
    setInnerDataSize(1);
}

double SinglySizedIndicator::data()
{
    return ar_data[0][m_nIndex];
}

void SinglySizedIndicator::popLast()
{
    ar_data[0].pop_back();
}

void SinglySizedIndicator::popFirst()
{
    ar_data[0].pop_front();
}

void SinglySizedIndicator::grow(size_t n)
{
    ar_data[0].resize(Size() + n);
}

void SinglySizedIndicator::setSize(size_t n)
{
    ar_data[0].reserve(n);
}



