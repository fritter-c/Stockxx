#include "pricecalc.h"
#include <cstddef>

SerieInterval PriceCalc::interval() const
{
    return m_interval;
}

PriceCalc::PriceCalc(CustomPrice *price) : IndicatorCalc(price)
{
    m_interval = price->interval();
}

PriceCalc::~PriceCalc()
{
    while(ar_values.count() > 0){
        delete ar_values[ar_values.count() - 1];
        ar_values.pop_back();
    }
    delete m_price;
}

void PriceCalc::CreateIndicatorsValues()
{
    bool bNext = true;
    Candle* candle;
    m_price->PriorAll();
    m_maxValue = m_price->High();
    m_minValue = m_price->Low();
    while(bNext){
        candle = new Candle(m_price->Data());
        ar_values.append(candle);
        if (m_price->High() > m_maxValue){
            m_maxValue = m_price->High();
        }
        if (m_minValue > m_price->Low()){
            m_minValue = m_price->Low();
        }
        bNext = m_price->Next();
    }

}

double PriceCalc::Open()
{
    return ar_values[m_nIndex]->dOpen;
}

double PriceCalc::Close()
{
    return ar_values[m_nIndex]->dClose;
}

QDateTime PriceCalc::Date()
{
    return ar_values[m_nIndex]->dtDate;
}

double PriceCalc::High()
{
    return ar_values[m_nIndex]->dHigh;
}

double PriceCalc::Low()
{
    return ar_values[m_nIndex]->dLow;
}

double PriceCalc::Volume()
{
    return ar_values[m_nIndex]->dVolume;
}

double PriceCalc::Max()
{
    return m_maxValue;
}

double PriceCalc::Min()
{
    return m_minValue;
}

QuoteIdentifier PriceCalc::Quote()
{
    return ar_values[m_nIndex]->qi;
}

Candle *PriceCalc::getCandle()
{
    return ar_values[m_nIndex];
}

Candle *PriceCalc::getCandle(QuoteIdentifier qi)
{
    GoToQuote(qi);
    return getCandle();
}

QList<Candle *> PriceCalc::getCandles()
{
    return ar_values;
}

bool PriceCalc::Next()
{
    if((m_nIndex + 1) <= (Size() - 1)){
        m_nIndex++;
        return true;
    }
    return false;
}

bool PriceCalc::Prior()
{
    if((m_nIndex - 1) >= 0){
        m_nIndex--;
        return true;
    }
    return false;

}

bool PriceCalc::PriorAll()
{
    m_nIndex = 0;
    return true;
}

bool PriceCalc::NextAll()
{
    m_nIndex = Size() - 1;
    return true;
}

bool PriceCalc::PriorN(size_t N)
{
    if((m_nIndex - N) >= 0){
        m_nIndex = m_nIndex - N;
        return true;
    }
    return false;
}

bool PriceCalc::NextN(size_t N)
{
    if((m_nIndex + N) <= (Size()-1)){
        m_nIndex = m_nIndex + N;
        return true;
    }
    return false;
}

size_t PriceCalc::Size()
{
    return ar_values.size();
}

void PriceCalc::GoToQuote(QuoteIdentifier qi)
{
    long long i{static_cast<long long>(Quote().id - qi.id)};
    if (i > 0){
        PriorN(i);
    }
    else{
        NextN(abs(i));
    }
}