#ifndef MINUTEDATASERIE_H
#define MINUTEDATASERIE_H

#include "customdataserie.h"

class MinuteDataSerie : public CustomDataSerie
{
private:
    const QString strPathSufix = "_M.dat";
    const QString strFolder = "minute\\";
    int m_nOffset{5};

    // CustomDataSerie interface
protected:
    virtual void loadSerieFromCSV(QString path, QChar delimiter) override;
    virtual void loadSerieFromStream() override;
    virtual void serieToStream() override;
    virtual void createId() override;

public:
    MinuteDataSerie(AssetId assetId,int offset, bool bLoad = true);
    virtual void loadSerieFromJsonAV(QString json) override;

    int nOffset() const;
};




#endif // MINUTEDATASERIE_H
