#ifndef DAILYDATASERIE_H
#define DAILYDATASERIE_H

#include "customdataserie.h"

class DailyDataSerie : public CustomDataSerie
{
    // CustomDataSerie interface
protected:
    virtual void LoadSerieFromStream() override;
    virtual void SerieToStream() override;
    virtual void LoadSerieFromCSV(QString path, QChar delimiter) override;
public:
    DailyDataSerie(AssetId assetId);
};

#endif // DAILYDATASERIE_H
