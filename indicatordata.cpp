#include "indicatordata.h"

void IndicatorData::setInnerDataSize(uint n)
{
    ar_data.resize(n);
}

IndicatorData::IndicatorData()
{
    setInnerDataSize(1);
}

void IndicatorData::grow(size_t)
{

}

void IndicatorData::setSize(size_t)
{

}


double IndicatorData::data()
{
    return INVALID_DOUBLE;
}

bool IndicatorData::Next()
{
    if ((m_nIndex + 1) <= Size() - 1){
        m_nIndex++;
        return true;
    }
    return false;
}

bool IndicatorData::Prior()
{
    if((m_nIndex - 1) >= 0){
        m_nIndex--;
        return true;
    }
    return false;
}

bool IndicatorData::PriorAll()
{
    m_nIndex = 0;
    return true;
}

bool IndicatorData::NextAll()
{
    m_nIndex = Size() - 1;
    return true;
}

bool IndicatorData::PriorN(size_t N)
{
    if((m_nIndex - N) >= 0){
        m_nIndex = m_nIndex - N;
        return true;
    }
    return false;
}

bool IndicatorData::NextN(size_t N)
{
    if((m_nIndex + N) <= (Size()-1)){
        m_nIndex = m_nIndex + N;
        return true;
    }
    return false;
}

void IndicatorData::popLast()
{

}

void IndicatorData::popFirst()
{

}

size_t IndicatorData::Size()
{
    return ar_data[0].size();
}

size_t IndicatorData::InnerSize()
{
    return ar_data.size();
}

bool IndicatorData::goTo(size_t n)
{
    if (n < Size()){
        m_nIndex = n;
        return true;
    }
    return false;

}

QVector<double> &IndicatorData::operator[](size_t n)
{
    return ar_data[n];
}


