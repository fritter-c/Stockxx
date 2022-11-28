#ifndef SINGLYSIZEDINDICATOR_H
#define SINGLYSIZEDINDICATOR_H

#include "indicatordata.h"

class SinglySizedIndicator : public IndicatorData
{
public:
    SinglySizedIndicator();

    // IndicatorData interface
public:
    virtual double data() override;
    virtual void popLast() override;
    virtual void popFirst() override;
    virtual void grow(size_t) override;
    virtual void setSize(size_t) override;
};



#endif // SINGLYSIZEDINDICATOR_H
