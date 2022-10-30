#include "dailyprice.h"

DailyPrice::DailyPrice(DailyDataSerie* dataserie, QObject *parent)
    : CustomPrice{dataserie, parent}
{
    m_dailyDataSerie = dataserie;
    m_nIndex = 0;
}

bool DailyPrice::Next()
{
    if ((m_nIndex + 1) <= Size() - 1){
        m_nIndex++;
        return true;
    }
    return false;
}

bool DailyPrice::Prior()
{
    if((m_nIndex - 1) >= 0){
        m_nIndex--;
        return true;
    }
    return false;
}

bool DailyPrice::PriorAll()
{
    m_nIndex = 0;
    return true;
}

bool DailyPrice::NextAll()
{
    m_nIndex = Size() - 1;
    return true;
}

bool DailyPrice::PriorN(size_t N)
{
    if((m_nIndex - N) >= 0){
        m_nIndex = m_nIndex - N;
        return true;
    }
    return false;
}

bool DailyPrice::NextN(size_t N)
{
    if((m_nIndex + N) <= (Size()-1)){
        m_nIndex = m_nIndex + N;
        return true;
    }
    return false;
}

size_t DailyPrice::Size()
{
    return m_dailyDataSerie->Size();
}
