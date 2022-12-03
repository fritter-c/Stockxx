#ifndef CUSTOMINDICATORCALC_H
#define CUSTOMINDICATORCALC_H

#include "customseriecalc.h"

class CustomIndicatorCalc : public CustomSerieCalc
{
    Q_OBJECT
protected:
    CustomSerieCalc* m_baseIndicator;
    virtual void createIndicatorValues();
    virtual void resize(size_t n);
    virtual void grow(size_t n);
public:
    CustomIndicatorCalc(CustomSerieCalc* baseIndicator);
public slots:
    void onCalcSerieFull();
signals:
    void newData(int start);
};

#endif // CUSTOMINDICATORCALC_H
