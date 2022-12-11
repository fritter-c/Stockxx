#include "customindicatorcalc.h"

CustomIndicatorCalc::CustomIndicatorCalc(CustomSerieCalc* baseIndicator)
{
    m_baseIndicator = baseIndicator;
}

CustomIndicatorCalc::~CustomIndicatorCalc()
{
    delete m_baseIndicator;
}

void CustomIndicatorCalc::onCalcSerieFull(IndicatorIdentifier id)
{
    if (id == ID())
        createIndicatorValues();
}

IndicatorIdentifier CustomIndicatorCalc::ID() const
{
    return m_ID;
}

void CustomIndicatorCalc::setID(IndicatorIdentifier newNID)
{
    m_ID = newNID;
}

void CustomIndicatorCalc::createIndicatorValues()
{

}
