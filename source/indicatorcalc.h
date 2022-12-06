#ifndef INDICATORCALC_H
#define INDICATORCALC_H

#include <QObject>
#include "customprice.h"

class IndicatorCalc : public QObject
{
protected:
    CustomPrice* m_price;
    size_t m_nIndex;
public:
    IndicatorCalc(CustomPrice* price);
    virtual bool Next();
    virtual bool Prior();
    virtual bool PriorAll();
    virtual bool NextAll();
    virtual bool PriorN(size_t N);
    virtual bool NextN(size_t N);
    virtual void GoToQuote(QuoteIdentifier qt);
    virtual size_t Size();
    virtual void CreateIndicatorsValues();
    virtual size_t nIndex() const;
};

#endif // INDICATORCALC_H
