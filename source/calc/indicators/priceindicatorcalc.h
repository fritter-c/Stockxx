#ifndef PRICEINDICATORCALC_H
#define PRICEINDICATORCALC_H

#include "customindicatorcalc.h"
#include "IndicatorDataTypes.h"

class PriceIndicatorCalc : public CustomIndicatorCalc
{
    Q_OBJECT
protected:
    CandleArray m_arData;
    virtual void createIndicatorValues() override;
    virtual void resize(size_t n);
    virtual void grow(size_t n);
    virtual void loadParams(IndicatorParamList) override{};
public:
    PriceIndicatorCalc(CustomSerieCalc* base);

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
    const CandleArray &getData() const;
};
#endif // PRICEINDICATORCALC_H