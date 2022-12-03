#include "indicatorcalc.h"

void IndicatorCalc::CreateIndicatorsValues()
{

}

size_t IndicatorCalc::nIndex() const
{
    return m_nIndex;
}

IndicatorCalc::IndicatorCalc(CustomPrice* price)
{
    m_price = price;
    m_nIndex = 0;
}

bool IndicatorCalc::Next()
{
    return false;
}

bool IndicatorCalc::Prior()
{
    return false;
}

bool IndicatorCalc::PriorAll()
{
    return false;
}

bool IndicatorCalc::NextAll()
{
    return false;
}

bool IndicatorCalc::PriorN(size_t N)
{
    return false;
}

bool IndicatorCalc::NextN(size_t N)
{
    return false;
}

void IndicatorCalc::GoToQuote(QuoteIdentifier qt)
{

}

size_t IndicatorCalc::Size()
{
    return 0;
}

