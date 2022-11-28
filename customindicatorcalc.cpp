#include "customindicatorcalc.h"

const IndicatorIdentifier &CustomIndicatorCalc::id() const
{
    return m_id;
}

CustomIndicatorCalc::CustomIndicatorCalc(CustomSerie *baseSerie)
{
    m_baseSerie = baseSerie;
}

size_t CustomIndicatorCalc::Size()
{
    return m_data->Size();
}

size_t CustomIndicatorCalc::Width()
{
    return m_data->InnerSize();
}

double CustomIndicatorCalc::Value()
{
    return INVALID_DOUBLE;
}

void CustomIndicatorCalc::createIndicatorValues()
{

}

QVector<double> &CustomIndicatorCalc::operator[](size_t n)
{
    return (*m_data)[n];
}

void CustomIndicatorCalc::onCreateIndicatorFull()
{
    createIndicatorValues();
}
