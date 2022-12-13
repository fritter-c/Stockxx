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
    virtual void addNewValue(size_t, size_t, DoublyArray*) override;
    double Value();
};


#endif // MOVINGAVERAGE_H
