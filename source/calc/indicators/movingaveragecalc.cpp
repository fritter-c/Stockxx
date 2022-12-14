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
    m_calcOver = (IndicatorCalcOver)params[2].integer;
    m_shift = params[3].integer;
}

void MovingAverageCalc::createIndicatorValues()
{
    resize(m_baseIndicator->Size());
    m_baseIndicator->PriorAll();

    size_t nIndex = 0;
    double dSum = 0;
    if (m_interval > m_baseIndicator->Size()) return;
    while (nIndex < m_interval - 1){
        m_arData[0][nIndex] = INVALID_DOUBLE;
        m_baseIndicator->Next();
        nIndex++;
    }

    do{
        // tem um jeito melhor de calcular isso mas por hora deixo assim
        size_t stepIndex{0};
        do{
            switch (m_calcOver) {
            case icClose: dSum+= m_baseIndicator->Close(); break;
            case icOpen : dSum+= m_baseIndicator->Open(); break;
            case icHigh : dSum+= m_baseIndicator->High(); break;
            case icLow  : dSum+= m_baseIndicator->Low(); break;
            }
            stepIndex++;
        }while((stepIndex < (m_interval)) and (m_baseIndicator->Prior()));
        m_baseIndicator->NextN(m_interval - 1);
        m_arData[0][nIndex] = dSum / m_interval;
        dSum = 0;
        nIndex++;
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
