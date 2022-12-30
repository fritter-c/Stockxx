#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include "customarrayindicator.h"

class MovingAverage : public CustomArrayIndicator
{
    Q_OBJECT
protected:
    virtual void resize(size_t n) override;
    virtual void grow(size_t n) override;

public:
    MovingAverage(CustomSerie* base);
    double Value() override;
    virtual QVector<double> Values() override;
};

#endif // MOVINGAVERAGE_H
