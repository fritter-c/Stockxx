#include "customarrayindicatorcalc.h"
#include "indicatormanager.h"

CustomArrayIndicatorCalc::CustomArrayIndicatorCalc(CustomSerieCalc * base) : CustomIndicatorCalc{base}
{
    m_arData.resize(1);
}

void CustomArrayIndicatorCalc::setInnerSize(size_t N)
{
    if (N > 0)
        m_arData.resize(N);
}

void CustomArrayIndicatorCalc::createIndicatorValues()
{
    IndicatorManager::Instance().addNewIndicatorData(ID(), 0, Size());
}

bool CustomArrayIndicatorCalc::Next()
{
    if ((m_nIndex + 1) <= Size() - 1){
        m_nIndex++;
        return true;
    }
    return false;
}

bool CustomArrayIndicatorCalc::Prior()
{
    if((m_nIndex - 1) >= 0){
        m_nIndex--;
        return true;
    }
    return false;
}

bool CustomArrayIndicatorCalc::PriorAll()
{
    m_nIndex = 0;
    return true;
}

bool CustomArrayIndicatorCalc::NextAll()
{
    m_nIndex = Size() - 1;
    return true;
}

bool CustomArrayIndicatorCalc::PriorN(size_t N)
{
    if((m_nIndex) >= N){
        m_nIndex = m_nIndex - N;
        return true;
    }
    return false;
}

bool CustomArrayIndicatorCalc::NextN(size_t N)
{
    if((m_nIndex + N) <= (Size()-1)){
        m_nIndex = m_nIndex + N;
        return true;
    }
    return false;
}

size_t CustomArrayIndicatorCalc::Size()
{
    return m_arData[0].size();
}

double CustomArrayIndicatorCalc::Open()
{
    return INVALID_DOUBLE;
}

double CustomArrayIndicatorCalc::Close()
{
    return INVALID_DOUBLE;
}

QDateTime CustomArrayIndicatorCalc::Date()
{
    return ZERO_DATE;
}

double CustomArrayIndicatorCalc::High()
{
    return INVALID_DOUBLE;
}

double CustomArrayIndicatorCalc::Low()
{
    return INVALID_DOUBLE;
}

double CustomArrayIndicatorCalc::Volume()
{
    return INVALID_DOUBLE;
}

QuoteIdentifier CustomArrayIndicatorCalc::Quote()
{
    return INVALID_QUOTE;
}

const DoublyArray &CustomArrayIndicatorCalc::getData() const
{
    return m_arData;
}
