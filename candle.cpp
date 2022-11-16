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

Candle::Candle(DataSerieValue * value)
{
    this->dClose = value->dClose;
    this->dHigh = value->dHigh;
    this->dLow = value->dLow;
    this->dOpen = value->dOpen;
    this->dtDate = value->dtQuoteDate;
    this->dVolume = value->dVolume;
    this->qi = value->qiQuote;
    SetCandleType();

}

