#include "customdataserie.h"

void CustomDataSerie::LoadSerieFromCSV(QString path, QChar delimiter)
{

}

void CustomDataSerie::LoadSerieFromStream()
{

}

void CustomDataSerie::SerieToStream()
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
    this->assetID = assetID;
}

size_t CustomDataSerie::Size()
{
    return ar_values.size();
}
