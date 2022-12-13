#include "priceindicator.h"

PriceIndicator::PriceIndicator(CustomSerie *base) : CustomIndicator{base}
{

}
void PriceIndicator::resize(size_t n)
{
    m_arData.resize(n);
}

void PriceIndicator::grow(size_t n)
{
    m_arData.resize(Size() + n);
}

bool PriceIndicator::Next()
{
    if ((m_nIndex + 1) <= Size() - 1){
        m_nIndex++;
        return true;
    }
    return false;
}

bool PriceIndicator::Prior()
{
    if((m_nIndex - 1) >= 0){
        m_nIndex--;
        return true;
    }
    return false;
}

bool PriceIndicator::PriorAll()
{
    m_nIndex = 0;
    return true;
}

bool PriceIndicator::NextAll()
{
    m_nIndex = Size() - 1;
    return true;
}

bool PriceIndicator::PriorN(size_t N)
{
    if((m_nIndex - N) >= 0){
        m_nIndex = m_nIndex - N;
        return true;
    }
    return false;
}

bool PriceIndicator::NextN(size_t N)
{
    if((m_nIndex + N) <= (Size()-1)){
        m_nIndex = m_nIndex + N;
        return true;
    }
    return false;
}

size_t PriceIndicator::Size()
{
    return m_arData.size();
}

double PriceIndicator::Open()
{
   return m_arData[m_nIndex].dOpen;
}

double PriceIndicator::Close()
{
   return m_arData[m_nIndex].dClose;
}

QDateTime PriceIndicator::Date()
{
  return m_arData[m_nIndex].dtDate;
}

double PriceIndicator::High()
{
    return m_arData[m_nIndex].dHigh;
}

double PriceIndicator::Low()
{
    return m_arData[m_nIndex].dLow;
}

double PriceIndicator::Volume()
{
    return m_arData[m_nIndex].dVolume;
}

void PriceIndicator::addNewPrice(size_t start, size_t count, CandleArray* values)
{
    if (start == 0)
        resize(count);
    else if (count > Size())
        grow(Size() - count);

    if(values->size() != m_arData.size()) return;

    for(size_t i{start}; i < m_arData.size(); ++i){
        m_arData[i] = (*values)[i - start];
    }
    emit NewData(start);
}

Candle PriceIndicator::Candle()
{
    return m_arData[m_nIndex];
}

bool PriceIndicator::GoToQuote(QuoteIdentifier qi)
{
    long long i{ static_cast<long long>(Quote().id - qi.id) };
    if (i > 0) {
        return NextN(i);
    }
    else {
        return PriorN(abs(i));
    }
};

bool PriceIndicator::GoToQuote(size_t q)
{
    long long i{ static_cast<long long>(m_nIndex - q) };
    if (i > 0) {
        return NextN(i);
    }
    else {
        return PriorN(abs(i));
    }
}

QuoteIdentifier PriceIndicator::Quote()
{
    return m_arData[m_nIndex].qi;
}

CandleArray PriceIndicator::GetCandles()
{
    return m_arData;
}

SerieInterval PriceIndicator::Interval()
{
    return m_baseIndicator->Interval();
}

bool PriceIndicator::GoToIndex(size_t n)
{
    if ((n > 0) and (n < Size())) {
        m_nIndex = n;
        return true;
    }
    return false;
}

double PriceIndicator::Max()
{
    // the maximum value will be the same of the base indicator which is a customprice
    return m_baseIndicator->Max();
}

double PriceIndicator::Min()
{
    // the minimun value will be the same of the base indicator which is a customprice
    return m_baseIndicator->Min();
}
