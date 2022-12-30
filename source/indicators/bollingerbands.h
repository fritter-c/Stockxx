#ifndef BOLLINGERBANDS_H
#define BOLLINGERBANDS_H

#include "customarrayindicator.h"

class BollingerBands : public CustomArrayIndicator
{
    // CustomArrayIndicator interface
    Q_OBJECT
protected:
    virtual void resize(size_t n) override;
    virtual void grow(size_t n) override;

public:
    BollingerBands(CustomSerie *base);
    virtual double Value() override;
    virtual QVector<double> Values() override;
};




#endif // BOLLINGERBANDS_H
