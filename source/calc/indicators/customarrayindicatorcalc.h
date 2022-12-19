#ifndef CUSTOMARRAYINDICATORCALC_H
#define CUSTOMARRAYINDICATORCALC_H

#include "customindicatorcalc.h"
#include "IndicatorDataTypes.h"

class CustomArrayIndicatorCalc : public CustomIndicatorCalc
{
    Q_OBJECT
protected:
    DoublyArray m_arData;
    virtual void setInnerSize(size_t N);
    virtual void resize(size_t n) = 0;
    virtual void grow(size_t n) = 0;
    virtual void createIndicatorValues() override;
public:
    CustomArrayIndicatorCalc(CustomSerieCalc*base);
    // CustomSerieCalc interface
    virtual bool Next() override;
    virtual bool Prior() override;
    virtual bool PriorAll() override;
    virtual bool NextAll() override;
    virtual bool PriorN(size_t N) override;
    virtual bool NextN(size_t N) override;
    virtual size_t Size() override;
    virtual double Open() override;
    virtual double Close() override;
    virtual QDateTime Date() override;
    virtual double High() override;
    virtual double Low() override;
    virtual double Volume() override;
    virtual QuoteIdentifier Quote() override;
    const DoublyArray &getData() const;
};
#endif // CUSTOMARRAYINDICATORCALC_H
