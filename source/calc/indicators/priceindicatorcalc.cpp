#include "priceindicatorcalc.h"
#include "custompricecalc.h"

PriceIndicatorCalc::PriceIndicatorCalc(CustomSerieCalc *base) : CustomIndicatorCalc{base}
{
    
}

void PriceIndicatorCalc::createIndicatorValues()
{
    CustomPriceCalc* price = dynamic_cast<CustomPriceCalc*>(m_baseIndicator);
    price->PriorAll();
    resize(price->Size());
    size_t i{0};
    do{
       m_arData[i] = Candle(price->Data());
    }while((price->Next()) and (++i));

    CustomIndicatorCalc::createIndicatorValues();
}

void PriceIndicatorCalc::resize(size_t n)
{
    m_arData.resize(n);
}

bool PriceIndicatorCalc::Next()
{
    if ((m_nIndex + 1) <= Size() - 1){
        m_nIndex++;
        return true;
    }
    return false;
}

bool PriceIndicatorCalc::Prior()
{
    if((m_nIndex - 1) >= 0){
        m_nIndex--;
        return true;
    }
    return false;
}

bool PriceIndicatorCalc::PriorAll()
{
    m_nIndex = 0;
    return true;
}

bool PriceIndicatorCalc::NextAll()
{
    m_nIndex = Size() - 1;
    return true;
}

bool PriceIndicatorCalc::PriorN(size_t N)
{
    if((m_nIndex - N) >= 0){
        m_nIndex = m_nIndex - N;
        return true;
    }
    return false;
}

bool PriceIndicatorCalc::NextN(size_t N)
{
    if((m_nIndex + N) <= (Size()-1)){
        m_nIndex = m_nIndex + N;
        return true;
    }
    return false;
}

size_t PriceIndicatorCalc::Size()
{
    return m_arData.size();
}

double PriceIndicatorCalc::Open()
{
   return m_arData[m_nIndex].dOpen;
}

double PriceIndicatorCalc::Close()
{
   return m_arData[m_nIndex].dClose;
}

QDateTime PriceIndicatorCalc::Date()
{
  return m_arData[m_nIndex].dtDate;
}

double PriceIndicatorCalc::High()
{
    return m_arData[m_nIndex].dHigh;
}

double PriceIndicatorCalc::Low()
{
    return m_arData[m_nIndex].dLow;
}

double PriceIndicatorCalc::Volume()
{
    return m_arData[m_nIndex].dVolume;
}
