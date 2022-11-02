#ifndef PRICECALC_H
#define PRICECALC_H

#include "indicatorcalc.h"
#include "candle.h"

class PriceCalc : public IndicatorCalc
{
private:
    QVector<Candle*> ar_values;
    double m_maxValue = 0;
    double m_minValue = 0;
public:
    PriceCalc(CustomPrice* price);
    virtual bool Next() override;
    virtual bool Prior() override;
    virtual bool PriorAll() override;
    virtual bool NextAll() override;
    virtual bool PriorN(size_t N) override;
    virtual bool NextN(size_t N) override;
    virtual size_t Size() override;
    virtual void GoToQuote(QuoteIdentifier qi) override;
    virtual void CreateIndicatorsValues() override;
    double Open();
    double Close();
    QDateTime Date();
    double High();
    double Low();
    double Volume();
    double Max();
    double Min();
    QuoteIdentifier Quote();
    Candle* getCandle();
    Candle* getCandle(QuoteIdentifier qi);
    QList<Candle*> getCandles();
};

#endif // PRICECALC_H
