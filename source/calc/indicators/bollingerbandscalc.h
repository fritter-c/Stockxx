#ifndef BOLLINGERBANDSCALC_H
#define BOLLINGERBANDSCALC_H

#include "movingaveragecalc.h"
#include <customarrayindicatorcalc.h>

class BollingerBandsCalc : public CustomArrayIndicatorCalc
{
private:
    int m_interval;
    MovingAverageType m_type;
    IndicatorCalcOver m_calcOver;
    double m_stdDev;
    MovingAverageCalc* m_movingAverage;
protected:
    virtual void loadParams(IndicatorCalcParams) override;
    virtual void resize(size_t n) override;
    virtual void grow(size_t n) override;
    virtual void createIndicatorValues() override;
public:
    BollingerBandsCalc(CustomSerieCalc* base, IndicatorCalcParams);



};


#endif // BOLLINGERBANDSCALC_H
