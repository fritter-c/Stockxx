#ifndef CUSTOMINDICATORCALC_H
#define CUSTOMINDICATORCALC_H

#include "IndicatorDataTypes.h"
#include "customseriecalc.h"

class CustomIndicatorCalc : public CustomSerieCalc
{
    Q_OBJECT
private:
    IndicatorIdentifier m_ID;
protected:
    CustomSerieCalc* m_baseIndicator;
    virtual void createIndicatorValues();
    virtual void loadParams(IndicatorCalcParams) = 0;
public:
    CustomIndicatorCalc(CustomSerieCalc* baseIndicator);
    ~CustomIndicatorCalc();
    IndicatorIdentifier ID() const;
    void setID(IndicatorIdentifier newNID);

public slots:
    void onCalcSerieFull(IndicatorIdentifier);
};
#endif // CUSTOMINDICATORCALC_H
