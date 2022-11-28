#ifndef MOVINGAVERAGECALC_H
#define MOVINGAVERAGECALC_H

#include "customindicatorcalc.h"

class MovingAverageCalc : public CustomIndicatorCalc
{
private:
    int m_interval;
public:
    MovingAverageCalc(CustomSerie* price, int interval);
    virtual double Value() override;
    void createIndicatorValues() override;
};



#endif // MOVINGAVERAGECALC_H
