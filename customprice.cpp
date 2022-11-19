#include "customprice.h"

SerieInterval CustomPrice::interval() const
{
    return m_interval;
}

CustomPrice::CustomPrice(CustomDataSerie *dataSerie, QObject *parent)
    : QObject{parent}
{
    m_dataSerie = dataSerie;
    m_interval = dataSerie->ID().si;
    m_nIndex = 0;
}

bool CustomPrice::Next()
{
    if ((m_nIndex + 1) <= Size() - 1){
        m_nIndex++;
        return true;
    }
    return false;
}

bool CustomPrice::Prior()
{
    if((m_nIndex - 1) >= 0){
        m_nIndex--;
        return true;
    }
    return false;
}

bool CustomPrice::PriorAll()
{
    m_nIndex = 0;
    return true;
}

bool CustomPrice::NextAll()
{
    m_nIndex = Size() - 1;
    return true;
}

bool CustomPrice::PriorN(size_t N)
{
    if((m_nIndex - N) >= 0){
        m_nIndex = m_nIndex - N;
        return true;
    }
    return false;
}

bool CustomPrice::NextN(size_t N)
{
    if((m_nIndex + N) <= (Size()-1)){
        m_nIndex = m_nIndex + N;
        return true;
    }
    return false;
}

size_t CustomPrice::Size()
{
    return m_dataSerie->Size();
}

double CustomPrice::Open()
{
    return m_dataSerie->ar_values[m_nIndex]->dOpen;
}

double CustomPrice::Close()
{
    return m_dataSerie->ar_values[m_nIndex]->dClose;
}

QDateTime CustomPrice::Date()
{
    return m_dataSerie->ar_values[m_nIndex]->dtQuoteDate;
}

double CustomPrice::High()
{
    return m_dataSerie->ar_values[m_nIndex]->dHigh;
}

double CustomPrice::Low()
{
    return m_dataSerie->ar_values[m_nIndex]->dLow;
}

double CustomPrice::Volume()
{
    return m_dataSerie->ar_values[m_nIndex]->dVolume;
}

DataSerieValue* CustomPrice::Data()
{
    return m_dataSerie->ar_values[m_nIndex];
}

QuoteIdentifier CustomPrice::Quote()
{
    return m_dataSerie->ar_values[m_nIndex]->qiQuote;
}
