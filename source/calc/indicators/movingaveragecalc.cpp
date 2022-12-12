#include "movingaveragecalc.h"
#include "indicatormanager.h"

MovingAverageCalc::MovingAverageCalc(CustomSerieCalc* base, IndicatorCalcParams params) : CustomArrayIndicatorCalc{base}
{
    MovingAverageCalc::loadParams(params);
}
void MovingAverageCalc::loadParams(IndicatorCalcParams params)
{
    m_interval = params[0].integer;
    m_type = (MovingAverageType)params[1].integer;
}

void MovingAverageCalc::createIndicatorValues()
{
    resize(m_baseIndicator->Size());
    m_baseIndicator->PriorAll();
    do{

    } while(m_baseIndicator->Next());
    IndicatorManager::Instance().addNewIndicatorData(ID(), 0, Size());
}

void MovingAverageCalc::resize(size_t n)
{
    m_arData[0].resize(n);
}

void MovingAverageCalc::grow(size_t n)
{
    m_arData[0].resize(Size() + n);
}

double MovingAverageCalc::Value()
{
    return m_arData[0][m_nIndex];
}
