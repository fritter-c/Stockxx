#ifndef CANDLE_H
#define CANDLE_H

#include "StockxxDataTypes.h"
#include <QDateTime>
enum CandleType {ctHarami = 0, ctBull = 1, ctBear = 2};

class Candle
{
private:
    void SetCandleType();
    qreal m_rGraphXValue{-1};
public:
    Candle(DataSerieValue*);
    Candle(DataSerieValue);
    Candle();
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
inline bool operator!=(const Candle& a, const Candle& b) {
    return (!(a.qi == b.qi));
}
inline Candle const INVALID_CANDLE = Candle();
#endif // CANDLE_H
