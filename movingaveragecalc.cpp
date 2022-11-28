#include "movingaveragecalc.h"
#include "singlysizedindicator.h"

MovingAverageCalc::MovingAverageCalc(CustomSerie *price, int interval) : CustomIndicatorCalc{price}
{
    m_data = new SinglySizedIndicator();
    m_interval = interval;
}

double MovingAverageCalc::Value()
{
    if (m_data->goTo(m_nIndex)){
        return m_data->data();
    }
    else{
        return INVALID_DOUBLE;
    }
}

void MovingAverageCalc::createIndicatorValues()
{
    m_baseSerie->PriorAll();
    m_data->setSize(m_baseSerie->Size());
    double sum{0};
    if (m_interval > m_baseSerie->Size()){
        for(int i{0}; i < m_baseSerie->Size(); ++i){
            (*m_data)[0][i] = INVALID_DOUBLE;
        }
        return;
    }
    int nIndex{0};
    while (nIndex < m_interval - 1)
    {
        (*m_data)[0][nIndex] = INVALID_DOUBLE;
        m_baseSerie->Next();
        nIndex++;
    }
    int nActualIndex{0};
    do{
        for(int i = 0; i < m_interval; ++i){
            sum += m_baseSerie->Close();
            m_baseSerie->Prior();
        }
        m_baseSerie->NextN(m_interval - 1);
        (*m_data)[0][m_interval + nActualIndex - 1] = sum / m_interval;
        nActualIndex++;
        sum = 0;
    }while(m_baseSerie->Next());
    emit NewData(0);

}
