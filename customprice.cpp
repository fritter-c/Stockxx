#include "customprice.h"

CustomPrice::CustomPrice(CustomDataSerie *dataSerie, QObject *parent)
    : QObject{parent}
{
    m_dataSerie = dataSerie;
}

bool CustomPrice::Next()
{
    return false;
}

bool CustomPrice::Prior()
{
    return false;
}

bool CustomPrice::PriorAll()
{
    return false;
}

bool CustomPrice::NextAll()
{
    return false;
}

bool CustomPrice::PriorN(size_t N)
{
    return false;
}

bool CustomPrice::NextN(size_t N)
{
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

QuoteIdentifier CustomPrice::Quote()
{
    return m_dataSerie->ar_values[m_nIndex]->qiQuote;
}
