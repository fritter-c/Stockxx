#include "customdataserie.h"

void CustomDataSerie::loadSerieFromCSV(QString path, QChar delimiter)
{

}

void CustomDataSerie::loadSerieFromStream()
{

}

void CustomDataSerie::serieToStream()
{

}

void CustomDataSerie::loadSerieFromJsonAV(QString json)
{

}

void CustomDataSerie::ClearDataSerie()
{
    for(size_t i{0}; i < ar_values.count(); i++)
    {
        delete ar_values[i];
    }
    ar_values.clear();
}

CustomDataSerie::CustomDataSerie(AssetId assetID)
{
    this->m_assetId = assetID;
}

size_t CustomDataSerie::Size()
{
    return ar_values.size();
}
