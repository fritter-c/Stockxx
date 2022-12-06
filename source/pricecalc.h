#ifndef PRICECALC_H
#define PRICECALC_H

#include "indicatorcalc.h"
#include "candle.h"
#include "qgraphicsitem.h"

class PriceCalc : public IndicatorCalc
{
    Q_OBJECT
private:
    QVector<Candle*> ar_values;
    double m_maxValue = 0;
    double m_minValue = 0;
    SerieInterval m_interval;
    QTimer* m_randomPriceTick{nullptr};
    QGraphicsItem* visual;
public:
    PriceCalc(CustomPrice* price, QGraphicsItem* visual);
    ~PriceCalc();
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
    SerieInterval interval() const;
    void toggleRandomClose(bool);

private slots:
    void onTickTimer();

};

#endif // PRICECALC_H
