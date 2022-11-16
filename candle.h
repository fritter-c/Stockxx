#ifndef CANDLE_H
#define CANDLE_H

#include <QDateTime>
#include "StockxxDataTypes.h"
enum CandleType {ctHarami = 0, ctBull = 1, ctBear = 2};
class Candle
{
private:
    void SetCandleType();
    qreal m_rGraphXValue{-1};
public:
    Candle(DataSerieValue*);
    double dOpen;
    double dClose;
    double dHigh;
    double dLow;
    double dVolume;

    QDateTime dtDate;
    CandleType ct;
    qreal rGraphXValue() const;
    void setRGraphXValue(qreal newRGraphXValue);
    QuoteIdentifier qi;
};
inline bool operator==(const Candle &a, const Candle &b) {
    return a.qi == b.qi;
}
#endif // CANDLE_H
