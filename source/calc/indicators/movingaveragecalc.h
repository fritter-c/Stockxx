#ifndef MOVINGAVERAGECALC_H
#define MOVINGAVERAGECALC_H

#include "customarrayindicatorcalc.h"

class MovingAverageCalc : public CustomArrayIndicatorCalc
{
private:
    int m_interval;
    MovingAverageType m_type;
    // CustomIndicatorCalc interface
protected:
    virtual void createIndicatorValues() override;
    virtual void resize(size_t n) override;
    virtual void grow(size_t n) override;
    virtual void loadParams(IndicatorParamList) override;

public:
    MovingAverageCalc(CustomSerieCalc* base, IndicatorParamList);
    double Value();

};




#endif // MOVINGAVERAGECALC_H
