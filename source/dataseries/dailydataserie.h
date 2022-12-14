#ifndef DAILYDATASERIE_H
#define DAILYDATASERIE_H

#include "customdataserie.h"

class DailyDataSerie : public CustomDataSerie
{
private:
    const QString m_strPathSufix = "_D.dat";
    const QString m_strFolder = "\\daily\\";
    // CustomDataSerie interface
protected:
    virtual void loadSerieFromStream() override;
    virtual void serieToStream() override;
    virtual void loadSerieFromCSV(QString path, QChar delimiter) override;
    virtual void createId() override;

public:
    virtual void loadSerieFromJsonAV(QString json) override;
    DailyDataSerie(AssetId assetId, bool bLoad = true);
    ~DailyDataSerie();
};

#endif // DAILYDATASERIE_H
