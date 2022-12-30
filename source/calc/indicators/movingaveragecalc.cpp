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
}

inline
double ifthen(double a, double b, bool condition){
    if (condition){
        return a;
    }
    return b;
}
void MovingAverageCalc::createIndicatorValues()
{
    resize(m_baseIndicator->Size());
    m_baseIndicator->PriorAll();

    size_t nIndex = 0;
    double dSum = 0;
    if (m_interval > m_baseIndicator->Size()) return;

    while (nIndex < m_interval - 1){
        m_arData[0][nIndex].value = 0;
        m_arData[0][nIndex].valid = false;
        m_arData[0][nIndex].id = m_baseIndicator->Quote();
        m_baseIndicator->Next();
        nIndex++;
    }
    if (m_type == mtArithmetic){
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
            m_arData[0][nIndex].value = dSum / m_interval;
            m_arData[0][nIndex].valid = true;
            m_arData[0][nIndex].id = m_baseIndicator->Quote();
            dSum = 0;
            nIndex++;
        } while(m_baseIndicator->Next());

    }
    else if(m_type == mtExponential){
        const double WEIGHT = 2.0 /(double) (m_interval + 1);
        bool bFirst{true};
        do{
            if(bFirst){
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
                m_arData[0][nIndex].value = dSum / m_interval;
                m_arData[0][nIndex].valid = true;
                m_arData[0][nIndex].id = m_baseIndicator->Quote();
                dSum = 0;
                bFirst = false;
                nIndex++;

            }
            else{
                double price;
                switch (m_calcOver) {
                case icClose: price= m_baseIndicator->Close(); break;
                case icOpen : price= m_baseIndicator->Open(); break;
                case icHigh : price= m_baseIndicator->High(); break;
                case icLow  : price= m_baseIndicator->Low(); break;
                }
                m_arData[0][nIndex].value = WEIGHT * price +  m_arData[0][nIndex -1].value * (1 - WEIGHT);
                m_arData[0][nIndex].valid = true;
                m_arData[0][nIndex].id = m_baseIndicator->Quote();
                nIndex++;
            }
        } while(m_baseIndicator->Next());
    }
    if (m_bHasVisual)
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
    return m_arData[0][m_nIndex].value;
}

QuoteIdentifier MovingAverageCalc::Quote()
{
    return  m_arData[0][m_nIndex].id;
}
