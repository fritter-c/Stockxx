#include "customindicator.h"

CustomIndicator::CustomIndicator(CustomSerie* base)
{
    m_baseIndicator = base;
}

IndicatorIdentifier CustomIndicator::ID() const
{
    return m_ID;
}

void CustomIndicator::setID(IndicatorIdentifier newNID)
{
    m_ID = newNID;
}
