#include "bollingerbandscalc.h"
#include "indicatormanager.h"

BollingerBandsCalc::BollingerBandsCalc(CustomSerieCalc* base, IndicatorCalcParams params) : CustomArrayIndicatorCalc{base}
{
    BollingerBandsCalc::loadParams(params);
    m_movingAverage = new MovingAverageCalc(base, params);
    m_movingAverage->setHasVisual(false);
    setInnerSize(3);

}
void BollingerBandsCalc::loadParams(IndicatorCalcParams params)
{
    m_interval = params[0].integer;
    m_type = (MovingAverageType)params[1].integer;
    m_calcOver = (IndicatorCalcOver)params[2].integer;
    m_stdDev = params[3].real;
}

void BollingerBandsCalc::resize(size_t n)
{
    m_arData[0].resize(n);
    m_arData[1].resize(n);
    m_arData[2].resize(n);
}

void BollingerBandsCalc::grow(size_t n)
{
    m_arData[0].resize(Size() + n);
    m_arData[1].resize(Size() + n);
    m_arData[2].resize(Size() + n);
}

void BollingerBandsCalc::createIndicatorValues()
{
    m_movingAverage->onCalcSerieFull(AnonymousIndicator);
    m_movingAverage->PriorAll();
    resize(m_baseIndicator->Size());


    size_t nIndex = 0;
    double dSum = 0;
    if (m_interval > m_baseIndicator->Size()) return;

    PriorAll();
    m_baseIndicator->PriorAll();
    while (nIndex < m_interval - 1){
        m_arData[0][nIndex].value = 0;
        m_arData[0][nIndex].valid = false;
        m_arData[0][nIndex].id = m_baseIndicator->Quote();
        m_arData[1][nIndex].value = 0;
        m_arData[1][nIndex].valid = false;
        m_arData[1][nIndex].id = m_baseIndicator->Quote();
        m_arData[2][nIndex].value = 0;
        m_arData[2][nIndex].valid = false;
        m_arData[2][nIndex].id = m_baseIndicator->Quote();
        m_baseIndicator->Next();
        nIndex++;
    }
    m_movingAverage->NextN(m_interval - 1);
    do{
        // tem um jeito melhor de calcular isso mas por hora deixo assim
        size_t stepIndex{0};
        do{
            switch (m_calcOver) {
            case icClose: dSum+= pow(m_baseIndicator->Close() -m_movingAverage->Value(),2); break;
            case icOpen : dSum+= pow(m_baseIndicator->Open()- m_movingAverage->Value(),2); break;
            case icHigh : dSum+= pow(m_baseIndicator->High() - m_movingAverage->Value(),2); break;
            case icLow  : dSum+= pow(m_baseIndicator->Low() - m_movingAverage->Value(),2); break;
            }
            stepIndex++;
        }while((stepIndex < (m_interval)) and (m_baseIndicator->Prior()));
        m_baseIndicator->NextN(m_interval - 1);

        m_arData[0][nIndex].value = m_movingAverage->Value() + m_stdDev * sqrt(dSum/ m_interval);
        m_arData[0][nIndex].valid = true;
        m_arData[0][nIndex].id = m_baseIndicator->Quote();
        m_arData[1][nIndex].value = m_movingAverage->Value();
        m_arData[1][nIndex].valid = true;
        m_arData[1][nIndex].id = m_baseIndicator->Quote();
        m_arData[2][nIndex].value = m_movingAverage->Value() - m_stdDev * sqrt(dSum/ m_interval);
        m_arData[2][nIndex].valid = true;
        m_arData[2][nIndex].id = m_baseIndicator->Quote();

        dSum = 0;
        nIndex++;
    } while(m_baseIndicator->Next() and m_movingAverage->Next());
    if (m_bHasVisual)
        IndicatorManager::Instance().addNewIndicatorData(ID(), 0, Size());
}
