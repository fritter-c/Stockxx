#ifndef CUSTOMINDICATOR_H
#define CUSTOMINDICATOR_H

#include "IndicatorDataTypes.h"
#include <customserie.h>

class CustomIndicator : public CustomSerie
{
private:
    IndicatorIdentifier m_ID;
protected:
    CustomSerie* m_baseIndicator;
public:
    CustomIndicator(CustomSerie *base);
    IndicatorIdentifier ID() const;
    void setID(IndicatorIdentifier newNID);
};

#endif // CUSTOMINDICATOR_H
