#include "candle.h"

void Candle::SetCandleType()
{
    if(dClose > dOpen){
        ct = CandleType::ctBull;
    }
    else if (dClose < dOpen){
        ct = CandleType::ctBear;
    }
    else{
        ct = CandleType::ctHarami;
    }
}

qreal Candle::rGraphXValue() const
{
    return m_rGraphXValue;
}

void Candle::setRGraphXValue(qreal newRGraphXValue)
{
    m_rGraphXValue = newRGraphXValue;
}

Candle::Candle(double dOpen, double dClose, double dLow, double dHigh, QDateTime dt, QuoteIdentifier qi)
{
    this->dClose = dClose;
    this->dHigh = dHigh;
    this->dLow = dLow;
    this->dOpen = dOpen;
    this->dtDate = dt;
    this->qi = qi;
    SetCandleType();
}

