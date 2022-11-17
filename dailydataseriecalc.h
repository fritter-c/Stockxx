#ifndef DAILYDATASERIECALC_H
#define DAILYDATASERIECALC_H

#include "customdataseriecalc.h"

class DailyDataSerieCalc : public CustomDataSerieCalc
{
    Q_OBJECT
private:
    const QString strPathSufix = "_D.dat";
    // CustomDataSerie interface
protected:
    virtual void loadSerieFromStream() override;
    virtual void serieToStream() override;
    virtual void loadSerieFromCSV(QString path, QChar delimiter) override;

public:
    virtual void loadSerieFromJsonAV(QString json) override;
    DailyDataSerieCalc(AssetId assetId, bool bLoad = true);
    ~DailyDataSerieCalc();
};

#endif // DAILYDATASERIECALC_H
