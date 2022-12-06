#include "customdataserie.h"

void CustomDataSerie::loadSerieFromCSV(QString path, QChar delimiter)
{

}

void CustomDataSerie::loadSerieFromStream()
{

}

void CustomDataSerie::serieToStream()
{
    QFile file(m_strPath);
    if (!file.open(QIODevice::WriteOnly)) return;
    QDataStream out(&file);
    out << c_StreamStart;
    out << m_assetId.name;
    out.setVersion(QDataStream::Qt_6_0);
    DataSerieValue dt;
    for(long long i{0}; i < ar_values.count(); i++)
    {
        dt = *ar_values[i];
        out << dt.dOpen;
        out << dt.dHigh;
        out << dt.dLow;
        out << dt.dClose;
        out << dt.dVolume;
        out << dt.dTrades;
        out << dt.dtQuoteDate;
        out << dt.qiQuote.id;
    }
    file.close();
}

void CustomDataSerie::createId()
{

}

CustomDataSerieCalc *CustomDataSerie::calcSerie() const
{
    return m_calcSerie;
}

void CustomDataSerie::setCalcSerie(CustomDataSerieCalc *newCalcSerie)
{
    m_calcSerie = newCalcSerie;
}

const DataSerieIdentifier &CustomDataSerie::ID() const
{
    return m_ID;
}

void CustomDataSerie::loadSerieFromJsonAV(QString json)
{

}

void CustomDataSerie::ClearDataSerie()
{
    for(long long i{0}; i < ar_values.count(); i++)
    {
        delete ar_values[i];
    }
    ar_values.clear();
}

CustomDataSerie::CustomDataSerie(AssetId assetID)
{
    this->m_assetId = assetID;
    QDir dir(m_strBasePath);
    if (!dir.exists()){
        dir.mkdir(m_strBasePath);
    }
}

size_t CustomDataSerie::Size()
{
    return ar_values.size();
}


