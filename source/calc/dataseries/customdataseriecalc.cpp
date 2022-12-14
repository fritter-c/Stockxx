#include "customdataseriecalc.h"
#include "calcdaemon.h"

CustomDataSerieCalc::CustomDataSerieCalc(AssetId assetID)
{
    moveToThread(&CalcDaemon::Instance());
    this->m_assetId = assetID;
    QDir dir(m_strBasePath);
    if (!dir.exists()){
        dir.mkdir(m_strBasePath);
    }
}

void CustomDataSerieCalc::loadSerieFromCSV(QString path, QChar delimiter)
{

}

void CustomDataSerieCalc::loadSerieFromStream()
{

}

void CustomDataSerieCalc::serieToStream()
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
        dt = ar_values[i];
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
    emit serieReady(m_assetId);
}

void CustomDataSerieCalc::createId()
{

}

const DataSerieIdentifier &CustomDataSerieCalc::ID() const
{
    return m_ID;
}

void CustomDataSerieCalc::loadSerieFromJsonAV(QString json)
{

}

void CustomDataSerieCalc::ClearDataSerie()
{
    ar_values.clear();
}

void CustomDataSerieCalc::fixEmptySeries()
{
    if (ar_values.isEmpty()){
        ar_values.resize(1);
    }
}

size_t CustomDataSerieCalc::Size()
{
    return ar_values.size();
}

void CustomDataSerieCalc::onLoadSerieFromJsonAV(QString json)
{
    loadSerieFromJsonAV(json);

}
