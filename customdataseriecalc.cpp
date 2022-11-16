#include "customdataseriecalc.h"
#include "calcdaemon.h"


void CustomDataSerieCalc::loadSerieFromCSV(QString path, QChar delimiter)
{

}

void CustomDataSerieCalc::loadSerieFromStream()
{

}

void CustomDataSerieCalc::serieToStream()
{

}

void CustomDataSerieCalc::loadSerieFromJsonAV(QString json)
{

}

void CustomDataSerieCalc::ClearDataSerie()
{
    for(size_t i{0}; i < ar_values.count(); i++)
    {
        delete ar_values[i];
    }
    ar_values.clear();
}

CustomDataSerieCalc::CustomDataSerieCalc(AssetId assetID)
{
    moveToThread(&CalcDaemon::Instance());
    this->m_assetId = assetID;
}

size_t CustomDataSerieCalc::Size()
{
    return ar_values.size();
}

void CustomDataSerieCalc::onLoadloadSerieFromJsonAV(QString json)
{
    loadSerieFromJsonAV(json);
}
