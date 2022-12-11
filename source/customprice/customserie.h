#ifndef CUSTOMSERIE_H
#define CUSTOMSERIE_H

#include "IndicatorDataTypes.h"
#include <QObject>
#include <StockxxDataTypes.h>

class CustomSerie : public QObject
{
    Q_OBJECT
protected:
    size_t m_nIndex{0};
public:
    virtual bool Next() = 0;
    virtual bool Prior() = 0;
    virtual bool PriorAll() = 0;
    virtual bool NextAll() = 0;
    virtual bool PriorN(size_t N) = 0;
    virtual bool NextN(size_t N) = 0;
    virtual bool GoToQuote(QuoteIdentifier) = 0;
    virtual bool GoToQuote(size_t) = 0;
    virtual QuoteIdentifier Quote() = 0;
    virtual size_t Size() = 0;
    virtual double Open() = 0;
    virtual double Close() = 0;
    virtual QDateTime Date() = 0;
    virtual double High() = 0;
    virtual double Low() = 0;
    virtual double Volume() = 0;
    virtual size_t ActualIndex();
    virtual CandleArray GetCandles() = 0;
    virtual SerieInterval Interval() = 0;
    virtual double Max() = 0;
    virtual double Min() = 0;
};
#endif // CUSTOMSERIE_H
