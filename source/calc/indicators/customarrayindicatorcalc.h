#ifndef CUSTOMARRAYINDICATORCALC_H
#define CUSTOMARRAYINDICATORCALC_H

#include "customindicatorcalc.h"
#include "IndicatorDataTypes.h"

class CustomArrayIndicatorCalc : public CustomIndicatorCalc
{
protected:
    DoublyArray m_arData;
public:
    CustomArrayIndicatorCalc(CustomSerieCalc*base);
};

#endif // CUSTOMARRAYINDICATORCALC_H
