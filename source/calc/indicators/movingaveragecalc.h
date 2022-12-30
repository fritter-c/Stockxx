#ifndef MOVINGAVERAGECALC_H
#define MOVINGAVERAGECALC_H

#include "customarrayindicatorcalc.h"

class MovingAverageCalc : public CustomArrayIndicatorCalc
{
private:
    int m_interval;
    MovingAverageType m_type;
    IndicatorCalcOver m_calcOver;
    // CustomIndicatorCalc interface
protected:
    virtual void createIndicatorValues() override;
    virtual void resize(size_t n) override;
    virtual void grow(size_t n) override;
    virtual void loadParams(IndicatorCalcParams) override;
public:
    MovingAverageCalc(CustomSerieCalc* base, IndicatorCalcParams);
    double Value();
    virtual QuoteIdentifier Quote() override;
};
#endif // MOVINGAVERAGECALC_H
