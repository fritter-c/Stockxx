#include "bollingerbands.h"



BollingerBands::BollingerBands(CustomSerie*base) : CustomArrayIndicator{base}
{
    m_arData.resize(3);
    m_arData[0].resize(1);
    m_arData[1].resize(1);
    m_arData[2].resize(1);
}

double BollingerBands::Value()
{
    return m_arData[0][m_nIndex].value;
}

QVector<double> BollingerBands::Values()
{
    QVector<double> result{m_arData[0][m_nIndex].value, m_arData[1][m_nIndex].value, m_arData[2][m_nIndex].value};
    return result;
}

void BollingerBands::resize(size_t n)
{
    m_arData[0].resize(n);
    m_arData[1].resize(n);
    m_arData[2].resize(n);
}

void BollingerBands::grow(size_t n)
{
    m_arData[0].resize(Size() + n);
    m_arData[1].resize(Size() + n);
    m_arData[2].resize(Size() + n);
}

