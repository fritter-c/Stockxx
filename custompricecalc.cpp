#include "custompricecalc.h"

SerieInterval CustomPriceCalc::interval() const
{
    return m_interval;
}

CustomPriceCalc::CustomPriceCalc(CustomDataSerieCalc *dataSerie)
{
    m_dataSerie = dataSerie;
    m_interval = dataSerie->ID().si;
    m_nIndex = 0;
}

bool CustomPriceCalc::Next()
{
    if ((m_nIndex + 1) <= Size() - 1){
        m_nIndex++;
        return true;
    }
    return false;
}

bool CustomPriceCalc::Prior()
{
    if((m_nIndex - 1) >= 0){
        m_nIndex--;
        return true;
    }
    return false;
}

bool CustomPriceCalc::PriorAll()
{
    m_nIndex = 0;
    return true;
}

bool CustomPriceCalc::NextAll()
{
    m_nIndex = Size() - 1;
    return true;
}

bool CustomPriceCalc::PriorN(size_t N)
{
    if((m_nIndex - N) >= 0){
        m_nIndex = m_nIndex - N;
        return true;
    }
    return false;
}

bool CustomPriceCalc::NextN(size_t N)
{
    if((m_nIndex + N) <= (Size()-1)){
        m_nIndex = m_nIndex + N;
        return true;
    }
    return false;
}

size_t CustomPriceCalc::Size()
{
    return m_dataSerie->Size();
}

double CustomPriceCalc::Open()
{
    return m_dataSerie->ar_values[m_nIndex]->dOpen;
}

double CustomPriceCalc::Close()
{
    return m_dataSerie->ar_values[m_nIndex]->dClose;
}

QDateTime CustomPriceCalc::Date()
{
    return m_dataSerie->ar_values[m_nIndex]->dtQuoteDate;
}

double CustomPriceCalc::High()
{
    return m_dataSerie->ar_values[m_nIndex]->dHigh;
}

double CustomPriceCalc::Low()
{
    return m_dataSerie->ar_values[m_nIndex]->dLow;
}

double CustomPriceCalc::Volume()
{
    return m_dataSerie->ar_values[m_nIndex]->dVolume;
}

DataSerieValue* CustomPriceCalc::Data()
{
    return m_dataSerie->ar_values[m_nIndex];
}

QuoteIdentifier CustomPriceCalc::Quote()
{
    return m_dataSerie->ar_values[m_nIndex]->qiQuote;
}

bool CustomPriceCalc::goTo(size_t n)
{
    if(n < Size()){
        m_nIndex = n;
        return true;
    }
    else return false;
}
